SET( EXTENSION_NAME "Extensions_PostProcessingEffects")

# Create the extension library
ADD_LIBRARY(${EXTENSION_NAME}
  # Add all the cpp source files here
  SunModule.cpp
  EffectHandler.cpp
  Effects/Wobble.cpp
  Effects/Shadows.cpp
  Effects/SimpleBlur.cpp
  Effects/TwoPassBlur.cpp
  Effects/GaussianBlur.cpp
  Effects/Glow.cpp
  Effects/SimpleMotionBlur.cpp
  Effects/MotionBlur.cpp
  Effects/EdgeDetection.cpp
  Effects/Toon.cpp
  Effects/SimpleDoF.cpp
  Effects/VolumetricLightScattering.cpp
  Effects/GrayScale.cpp
  Effects/Pixelate.cpp
  Effects/Saturate.cpp
  Effects/ShowImage.cpp
  Effects/SimpleExample.cpp
  Effects/DoF.cpp
)

TARGET_LINK_LIBRARIES(${EXTENSION_NAME}
  Extensions_TGAResource
)