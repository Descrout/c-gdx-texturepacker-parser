#include "GdxTextureAtlas.h"
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

static void append_buffer(char *buffer, char c)
{
    char str[2] = {c, '\0'};
    strcat_s(buffer, BUFFER_SIZE, str);
}

static AtlasRectContainer *new_container()
{
    AtlasRectContainer *container = (AtlasRectContainer *)malloc(sizeof(AtlasRectContainer));
    if (container == NULL)
        return NULL;
    container->rects = NULL;
    container->count = 0;
    return container;
}

static int add_rect(AtlasRectContainer *container, AtlasRect *rect, int index)
{
    if (container == NULL)
        return 0;
    index += 1;
    if (container->rects == NULL || index > container->count)
    {
        AtlasRect *newRects = (AtlasRect *)realloc(container->rects, sizeof(AtlasRect) * index);
        if (newRects == NULL)
            return container->count;
        container->rects = newRects;
        container->count = index;
    }
    memcpy(&container->rects[index - 1], rect, sizeof(AtlasRect));
    return container->count;
}

static void free_container(AtlasRectContainer *container)
{
    if (container == NULL)
        return;
    if (container->rects != NULL)
        free(container->rects);
    free(container);
}

AtlasRectContainer *gdx_get_container(GdxTextureAtlas *atlas, const char *key)
{
    if (atlas == NULL)
        return NULL;
    return (AtlasRectContainer *)hm_get(atlas->map, key);
}

AtlasRect *gdx_get_rect(AtlasRectContainer *container, int index)
{
    if (index < 0 || container == NULL || index >= container->count)
    {
        return NULL;
    }

    return &container->rects[index];
}

GdxTextureAtlas *gdx_parse_atlas(const char *data, int capacity)
{
    GdxTextureAtlas *atlas = (GdxTextureAtlas *)malloc(sizeof(GdxTextureAtlas));
    if (atlas == NULL)
        return NULL;
    atlas->map = new_hashmap(capacity, &free_container);
    if (atlas->map == NULL)
    {
        free(atlas);
        return NULL;
    }

    char buffer[BUFFER_SIZE];
    *buffer = '\0';

    char currentName[BUFFER_SIZE];
    int currentIdx = 0;
    AtlasRect currentRect = {0};
    int currentField = 0;
    char skipCounter = 0;

    /*
    0 = Skip info.
    1 = Recording keyword.
    2 = Getting index.
    3 = Getting bounds.
    */
    int state = 0;

    for (const char *c = data; *c; c++)
    {
        switch (state)
        {
        case 0:
            if (*c == '\n')
                skipCounter += 1;
            if (skipCounter >= 3)
                state = 1;
            break;
        case 1:
            if (*c == '\n')
            {
                strcpy_s(currentName, BUFFER_SIZE, buffer);
                *buffer = '\0';
            }
            else if (*c == ':')
            {
                if (strcmp(buffer, "index") == 0)
                    state = 2;
                else if (strcmp(buffer, "bounds") == 0)
                    state = 3;
                *buffer = '\0';
            }
            else
            {
                append_buffer(buffer, *c);
            }
            break;
        case 2:
            if (*c == '\n')
            {
                currentIdx = atoi(buffer);
                state = 1;
                *buffer = '\0';
            }
            else
            {
                append_buffer(buffer, *c);
            }
            break;
        case 3:
            if (*c == '\n')
            {
                AtlasRectContainer *container = gdx_get_container(atlas, currentName);
                if (container == NULL)
                {
                    container = (AtlasRectContainer *)hm_put(atlas->map, currentName, new_container());
                }
                float val = (float)atoi(buffer);
                currentRect.height = val;
                add_rect(container, &currentRect, currentIdx);
                currentField = 0;
                currentIdx = 0;
                state = 1;
                *buffer = '\0';
            }
            else if (*c == ',')
            {
                float val = (float)atoi(buffer);
                if (currentField == 0)
                    currentRect.x = val;
                else if (currentField == 1)
                    currentRect.y = val;
                else if (currentField == 2)
                    currentRect.width = val;
                currentField++;
                *buffer = '\0';
            }
            else
            {
                append_buffer(buffer, *c);
            }
            break;
        default:
            break;
        }
    }

    return atlas;
}

void gdx_free_atlas(GdxTextureAtlas *atlas)
{
    if (atlas == NULL)
        return;
    free_hashmap(atlas->map);
    free(atlas);
}