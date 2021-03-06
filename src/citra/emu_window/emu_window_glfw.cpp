// Copyright 2014 Citra Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#include "common/common.h"

#include "video_core/video_core.h"

#include "citra/emu_window/emu_window_glfw.h"

static const std::pair<int, HID_User::PadState> default_key_map[] = {
    { GLFW_KEY_A, HID_User::PAD_A },
    { GLFW_KEY_B, HID_User::PAD_B },
    { GLFW_KEY_BACKSLASH, HID_User::PAD_SELECT },
    { GLFW_KEY_ENTER, HID_User::PAD_START },
    { GLFW_KEY_RIGHT, HID_User::PAD_RIGHT },
    { GLFW_KEY_LEFT, HID_User::PAD_LEFT },
    { GLFW_KEY_UP, HID_User::PAD_UP },
    { GLFW_KEY_DOWN, HID_User::PAD_DOWN },
    { GLFW_KEY_R, HID_User::PAD_R },
    { GLFW_KEY_L, HID_User::PAD_L },
    { GLFW_KEY_X, HID_User::PAD_X },
    { GLFW_KEY_Y, HID_User::PAD_Y },
    { GLFW_KEY_H, HID_User::PAD_CIRCLE_RIGHT },
    { GLFW_KEY_F, HID_User::PAD_CIRCLE_LEFT },
    { GLFW_KEY_T, HID_User::PAD_CIRCLE_UP },
    { GLFW_KEY_G, HID_User::PAD_CIRCLE_DOWN },
};

/// Called by GLFW when a key event occurs
void EmuWindow_GLFW::OnKeyEvent(GLFWwindow* win, int key, int scancode, int action, int mods) {

    if (!VideoCore::g_emu_window) {
        return;
    }

    int keyboard_id = ((EmuWindow_GLFW*)VideoCore::g_emu_window)->keyboard_id;

    if (action == GLFW_PRESS) {
        EmuWindow::KeyPressed({key, keyboard_id});
    }

    if (action == GLFW_RELEASE) {
        EmuWindow::KeyReleased({key, keyboard_id});
    }
    HID_User::PadUpdateComplete();
}

/// EmuWindow_GLFW constructor
EmuWindow_GLFW::EmuWindow_GLFW() {

    // Register a new ID for the default keyboard
    keyboard_id = KeyMap::NewDeviceId();

    // Set default key mappings for keyboard
    for (auto mapping : default_key_map) {
        KeyMap::SetKeyMapping({mapping.first, keyboard_id}, mapping.second);
    }

    // Initialize the window
    if(glfwInit() != GL_TRUE) {
        printf("Failed to initialize GLFW! Exiting...");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	
#if EMU_PLATFORM == PLATFORM_MACOSX
    // GLFW on OSX requires these window hints to be set to create a 3.2+ GL context.
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
	
    m_render_window = glfwCreateWindow(VideoCore::kScreenTopWidth, 
        (VideoCore::kScreenTopHeight + VideoCore::kScreenBottomHeight), 
        m_window_title.c_str(), NULL, NULL);

    if (m_render_window == NULL) {
        printf("Failed to create GLFW window! Exiting...");
        exit(1);
    }
    
    // Setup callbacks
    glfwSetWindowUserPointer(m_render_window, this);
    glfwSetKeyCallback(m_render_window, OnKeyEvent);

    DoneCurrent();
}

/// EmuWindow_GLFW destructor
EmuWindow_GLFW::~EmuWindow_GLFW() {
    glfwTerminate();
}

/// Swap buffers to display the next frame
void EmuWindow_GLFW::SwapBuffers() {
    glfwSwapBuffers(m_render_window);
}

/// Polls window events
void EmuWindow_GLFW::PollEvents() {
    glfwPollEvents();
}

/// Makes the GLFW OpenGL context current for the caller thread
void EmuWindow_GLFW::MakeCurrent() {
    glfwMakeContextCurrent(m_render_window);
}

/// Releases (dunno if this is the "right" word) the GLFW context from the caller thread
void EmuWindow_GLFW::DoneCurrent() {
    glfwMakeContextCurrent(NULL);
}
