cmake_minimum_required(VERSION 3.22)
project(CElay VERSION 0.0.1)

# JUCE liegt direkt eine Ebene höher
add_subdirectory(.. juce)

juce_add_plugin(CElay
    PLUGIN_MANUFACTURER_CODE Dman
    PLUGIN_CODE Dlay
    FORMATS VST3 AU
    IS_SYNTH FALSE
    PLUGIN_NAME "CElay")

target_sources(CElay PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginProcessor.h
    Source/PluginEditor.cpp
    Source/PluginEditor.h)

target_link_libraries(CElay PRIVATE
    juce::juce_audio_utils
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags)

target_compile_definitions(CElay PRIVATE
    JUCE_VST3_CAN_REPLACE_VST2=0
)