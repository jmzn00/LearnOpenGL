#include "Camera.h"

Camera::Camera()
{
    Position = glm::vec3(0.0f, 0.0f, 3.0f);
    WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    Yaw = YAW;
    Pitch = PITCH;

    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Zoom = ZOOM;

    updateCameraVectors();
}
Camera::Camera(glm::vec3 position, glm::vec3 worldUp, float yaw, float pitch)
{
    Position = position;
    WorldUp = worldUp;
    Yaw = yaw;
    Pitch = pitch;

    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    Zoom = ZOOM;

    updateCameraVectors();
}
void Camera::ProcessKeyboard(Camera_Movement dir, float dt)
{
    float vel = MovementSpeed * dt;

    glm::vec3 forward = glm::normalize(glm::vec3(Front.x, 0.0f, Front.z));
    glm::vec3 right = glm::normalize(glm::vec3(Right.x, 0.0f, Right.z));

    switch (dir)
    {
        case FORWARD:
            Position += forward * vel;
            break;
        case BACKWARD:
            Position -= forward * vel;
            break;
        case RIGHT:
            Position += right * vel;
            break;
        case LEFT:
            Position -= right * vel;
            break;
    }   
}
void Camera::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
    xOffset *= MouseSensitivity;
    yOffset *= MouseSensitivity;

    Yaw   += xOffset;
    Pitch += yOffset;

    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }
    updateCameraVectors();
}
void Camera::ProcessMouseScroll(float yOffset)
{
    Zoom -= (float)yOffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}
glm::mat4 Camera::calculate_lookAt_matrix(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
    glm::vec3 forward = glm::normalize(target - position);
    glm::vec3 right = glm::normalize(glm::cross(forward, worldUp));
    glm::vec3 up = glm::cross(right, forward);

    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = right.x;
    rotation[1][0] = right.y;
    rotation[2][0] = right.z;

    rotation[0][1] = up.x;
    rotation[1][2] = up.y;
    rotation[2][1] = up.z;

    rotation[0][2] = -forward.x;
    rotation[1][2] = -forward.y;
    rotation[2][2] = -forward.z;

    glm::mat4 translation = glm::mat4(1.0f);
    translation[3][0] = -position.x;
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;

    return rotation * translation;
}
glm::mat4 Camera::GetViewMatrix()
{
    return calculate_lookAt_matrix(Position, Position + Front, Up);
}