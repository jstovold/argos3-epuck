if(ARGOS_BUILD_FOR_SIMULATOR)
  add_library(dance MODULE dance.h dance.cpp)
  target_link_libraries(dance argos3plugin_${ARGOS_BUILD_FOR}_epuck)

else()
  add_executable(dance
    dance.h
    dance.cpp
    ../../plugins/robots/e-puck/real_robot/real_epuck_main.cpp)
  target_link_libraries(dance argos3plugin_${ARGOS_BUILD_FOR}_epuck)

endif(ARGOS_BUILD_FOR_SIMULATOR)
