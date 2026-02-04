cmake_minimum_required(VERSION 3.22)
project(SpectralConvolver VERSION 1.0.0)

add_subdirectory(JUCE)

juce_add_plugin(SpectralConvolver
    PRODUCT_NAME "SpectralConvolver"
    COMPANY_NAME "TaimBak"
    BUNDLE_ID "com.TaimBak.SpectralConvolver"
    PLUGIN_MANUFACTURER_CODE Manu
    PLUGIN_CODE Wyr3
    FORMATS VST3 AU Standalone
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    VST3_CATEGORIES Fx
    AU_MAIN_TYPE kAudioUnitType_Effect
    COPY_PLUGIN_AFTER_BUILD FALSE
)

juce_generate_juce_header(SpectralConvolver)

target_sources(SpectralConvolver
    PRIVATE
        src/FreqDomainConvolver.cpp
        src/FreqDomainConvolver.h
        src/TimeDomainConvolver.cpp
        src/TimeDomainConvolver.h
        src/PluginProcessor.cpp
        src/PluginProcessor.h
        src/PluginEditor.cpp
        src/PluginEditor.h
)

target_compile_definitions(SpectralConvolver
    PUBLIC
        JUCE_VST3_CAN_REPLACE_VST2=0
        JUCE_STRICT_REFCOUNTEDPOINTER=1
)

target_link_libraries(SpectralConvolver
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_processors
        juce::juce_audio_processors_headless
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_data_structures
        juce::juce_dsp
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_warning_flags
)

get_target_property(JUCE_INCLUDE_DIRS juce::juce_core INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${JUCE_INCLUDE_DIRS})