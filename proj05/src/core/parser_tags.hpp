#ifndef PARSER_TAGS_H
#define PARSER_TAGS_H

#include <climits>
#include <utility>



class ParserTags
{
public:
    inline static const char* PARSER_DEFAULT_STR = "N0T_F0UND";
    inline static const int PARSER_DEFAULT_INT = INT_MIN;
    inline static const float PARSER_DEFAULT_FLOAT = 0.0002f;

    // LOOK_AT
    inline static const char* LOOKAT = "lookat";
    inline static const char* LOOKAT_LOOK_FROM = "look_from";
    inline static const char* LOOKAT_LOOK_AT = "look_at";
    inline static const char* LOOKAT_UP = "up";

    // INTEGRATOR
    inline static const char* INTEGRATOR = "integrator";
    inline static const char* INTEGRATOR_TYPE = "type";
    inline static const char* INTEGRATOR_TYPE_FLAT = "flat";
    inline static const char* INTEGRATOR_TYPE_NORMAL_MAP = "normal_map";
    inline static const char* INTEGRATOR_TYPE_DEPTH_MAP = "depth_map";
    inline static const char* INTEGRATOR_DEPTH_MAP_ZMIN = "zmin";
    inline static const char* INTEGRATOR_DEPTH_MAP_ZMAX = "zmax";
    inline static const char* INTEGRATOR_DEPTH_MAP_NEAR_COLOR = "near_color";
    inline static const char* INTEGRATOR_DEPTH_MAP_FAR_COLOR = "far_color";

    // CAMERA
    inline static const char* CAMERA = "camera";
    inline static const char* CAMERA_TYPE = "type";
    inline static const char* CAMERA_TYPE_ORTOGRAPHIC = "ortographic";
    inline static const char* CAMERA_TYPE_PERSPECTIVE = "perspective";
    inline static const char* CAMERA_SCREEN_WINDOW = "screen_window";
    inline static const char* CAMERA_FOVY = "fovy";

    // FILM
    inline static const char* FILM = "film";
    inline static const char* FILM_TYPE = "type";
    inline static const char* FILM_X_RES = "x_res";
    inline static const char* FILM_Y_RES = "y_res";
    inline static const char* FILM_FILENAME = "filename";
    inline static const char* FILM_IMG_TYPE = "img_type";
    inline static const char* FILM_CROP_WINDOW = "crop_window";    // new
    inline static const char* FILM_GAMMA_CORRECTED = "gamma_corrected";    // new

    // INCLUDE
    inline static const char* INCLUDE = "include";
    inline static const char* INCLUDE_FILENAME = "filename";

    // SCENE ----------------------------------------------------------------
    inline static const char* SCENE_WORLD_BEGIN = "world_begin";
    inline static const char* SCENE_WORLD_END = "world_end";
    inline static const char* RENDER_AGAIN = "render_again";

    // BACKGROUND
    inline static const char* BACKGROUND = "background";
    inline static const char* BACKGROUND_TYPE = "type";
    inline static const char* BACKGROUND_MAPPING = "mapping";
    inline static const char* BACKGROUND_COLOR = "color";
    inline static const char* BACKGROUND_BL = "bl";
    inline static const char* BACKGROUND_TL = "tl";
    inline static const char* BACKGROUND_TR = "tr";
    inline static const char* BACKGROUND_BR = "br";

    // MATERIAL
    inline static const char* MATERIAL = "material";
    inline static const char* MAKE_NAMED_MATERIAL = "make_named_material";
    inline static const char* MATERIAL_TYPE = "type";
    inline static const char* MATERIAL_TYPE_FLAT = "flat";
    inline static const char* MATERIAL_TYPE_BLINN = "blinn";
    inline static const char* MATERIAL_BLINN_NAME = "name";
    inline static const char* MATERIAL_BLINN_AMBIENT = "ambient";
    inline static const char* MATERIAL_BLINN_DIFFUSE = "diffuse";
    inline static const char* MATERIAL_BLINN_SPECULAR = "specular";
    inline static const char* MATERIAL_BLINN_MIRROR = "mirror";
    inline static const char* MATERIAL_BLINN_GLOSSINESS = "glossiness";
    inline static const char* MATERIAL_COLOR = "color";

    // OBJECT
    inline static const char* OBJECT = "object";
    inline static const char* OBJECT_TYPE = "type";
    inline static const char* OBJECT_SPHERE = "sphere";
    inline static const char* OBJECT_RADIUS = "radius";
    inline static const char* OBJECT_CENTER = "center";

    // LIGHT
    inline static const char* LIGHT = "light_source";
    inline static const char* LIGHT_TYPE = "type";
    inline static const char* LIGHT_TYPE_AMBIENT = "ambient";
    inline static const char* LIGHT_TYPE_DIRECTIONAL = "directional";
    inline static const char* LIGHT_TYPE_POINT = "point";
    inline static const char* LIGHT_TYPE_SPOT = "spot";
    inline static const char* LIGHT_SPOT_CUTOFF = "cutoff";
    inline static const char* LIGHT_SPOT_FALLOFF = "falloff";
    inline static const char* LIGHT_I = "I";
    inline static const char* LIGHT_L = "L";
    inline static const char* LIGHT_FROM = "from";
    inline static const char* LIGHT_TO = "to";
    inline static const char* LIGHT_SCALE = "scale";
};

#endif