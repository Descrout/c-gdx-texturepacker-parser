# Gdx TexturePacker Parser in C

Usage
```c
GdxTextureAtlas *atlas = gdx_parse_atlas(str, 2000);
printf("LEN: %d\n\n", atlas->map->length);

AtlasRectContainer *angelContainer = gdx_get_container(atlas, "angel");
AtlasRect *rect = gdx_get_rect(angelContainer, 4);
printf("ANGEL[4] = x: %f, y: %f, w: %f, h: %f\n\n", rect->x, rect->y, rect->width, rect->height);

AtlasRectContainer *enemyContainer = gdx_get_container(atlas, "enemy-explode");
for (int i = 0; i < enemyContainer->count; i++)
{
    AtlasRect *rect = &enemyContainer->rects[i];
    printf("ENEMY-EXPLODE[%d] = x: %f, y: %f, w: %f, h: %f\n", i, rect->x, rect->y, rect->width, rect->height);
}

gdx_free_atlas(atlas);
```
Example Data
```c
char *str = "raylib.png\n"
            "size:2048,128\n"
            "repeat:none\n"
            "angel\n"
            "index:0\n"
            "bounds:2,2,122,117"
            "\n"
            "angel\n"
            "index:5\n"
            "bounds:126,2,122,117"
            "\n"
            "angel\n"
            "index:2\n"
            "bounds:250,2,122,117"
            "\n"
            "angel\n"
            "index:7\n"
            "bounds:374,2,122,117"
            "\n"
            "angel\n"
            "index:4\n"
            "bounds:622,2,122,117"
            "\n"
            "angel\n"
            "index:1\n"
            "bounds:746,2,122,117"
            "\n"
            "angel\n"
            "index:6\n"
            "bounds:870,2,122,117"
            "\n"
            "angel\n"
            "index:3\n"
            "bounds:1118,2,122,11"
            "7\n"
            "angel-attack\n"
            "index:1\n"
            "bounds:498,2,122,117"
            "\n"
            "angel-attack\n"
            "index:0\n"
            "bounds:994,2,122,117"
            "\n"
            "angel-attack\n"
            "index:2\n"
            "bounds:1242,2,122,11"
            "7\n"
            "blue-explode\n"
            "index:1\n"
            "bounds:1366,2,39,49"
            "\n"
            "blue-explode\n"
            "index:3\n"
            "bounds:1947,70,39,49"
            "\n"
            "blue-explode\n"
            "index:0\n"
            "bounds:1407,2,39,49"
            "\n"
            "blue-explode\n"
            "index:5\n"
            "bounds:1988,70,39,49"
            "\n"
            "blue-explode\n"
            "index:2\n"
            "bounds:1448,2,39,49"
            "\n"
            "blue-explode\n"
            "index:4\n"
            "bounds:1489,2,39,49"
            "\n"
            "enemy-explode\n"
            "index:4\n"
            "bounds:1366,53,81,66"
            "\n"
            "enemy-explode\n"
            "index:1\n"
            "bounds:1449,53,81,66"
            "\n"
            "enemy-explode\n"
            "index:6\n"
            "bounds:1532,53,81,66"
            "\n"
            "enemy-explode\n"
            "index:3\n"
            "bounds:1615,53,81,66"
            "\n"
            "enemy-explode\n"
            "index:0\n"
            "bounds:1698,53,81,66"
            "\n"
            "enemy-explode\n"
            "index:5\n"
            "bounds:1781,53,81,66"
            "\n"
            "enemy-explode\n"
            "index:2\n"
            "bounds:1864,53,81,66"
            "\n"
            "spikeball\n"
            "bounds:1530,19,32,32"
            "\n";
```