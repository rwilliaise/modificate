
#include <cglm/cam.h>
#include <client/render.h>

r_camera_t r_camera = {
    .pos = GLM_VEC3_ZERO_INIT,
    .fov = 70,
    .rot = GLM_QUAT_IDENTITY_INIT,
    .view = GLM_MAT4_IDENTITY_INIT
};

int r_camera_update() {
    if (r_win == NULL || r_win_height == 0 || r_win_height == 0) { return 1; }
    if (r_camera.fov == 0) {
        glm_ortho(
                -r_win_width,
                r_win_width,
                -r_win_height,
                r_win_height,
                1,
                1000,
                r_camera.view
        );
        return 0;
    }
    glm_perspective(r_camera.fov, (float) r_win_width / r_win_height, 1, 1000, r_camera.view);
    return 0;
}

