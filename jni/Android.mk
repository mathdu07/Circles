LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := circles

LOCAL_SRC_FILES := src/Main.cpp src/Game.cpp src/Assets.cpp src/Graphics.cpp src/Fonts.cpp \
              src/State.cpp src/MainMenuState.cpp src/CircleButton.cpp src/SettingsState.cpp \
              src/PlayState.cpp src/Circle.cpp src/TransitionState.cpp src/GameOverState.cpp 

LOCAL_SHARED_LIBRARIES := sfml-system
LOCAL_SHARED_LIBRARIES += sfml-window
LOCAL_SHARED_LIBRARIES += sfml-graphics
LOCAL_SHARED_LIBRARIES += sfml-audio
LOCAL_SHARED_LIBRARIES += sfml-network
LOCAL_WHOLE_STATIC_LIBRARIES := sfml-main
LOCAL_STATIC_LIBRARIES += sfml-ui

include $(BUILD_SHARED_LIBRARY)

$(call import-module,sfml)
$(call import-module,sfml-ui)
