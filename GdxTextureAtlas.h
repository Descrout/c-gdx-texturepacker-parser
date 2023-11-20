#pragma once
#include <hashmap.h>

struct AtlasRect
{
    float x;
    float y;
    float width;
    float height;
} typedef AtlasRect;

struct AtlasRectContainer
{
    AtlasRect *rects;
    int count;
} typedef AtlasRectContainer;

struct GdxTextureAtlas
{
    Hashmap *map;
} typedef GdxTextureAtlas;

AtlasRect *gdx_get_rect(AtlasRectContainer *container, int index);
GdxTextureAtlas *gdx_parse_atlas(const char *data, int capacity);
AtlasRectContainer *gdx_get_container(GdxTextureAtlas *atlas, const char *key);
void gdx_free_atlas(GdxTextureAtlas *atlas);