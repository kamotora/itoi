cmake_minimum_required(VERSION 3.19)
project(itoi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set(REQUIRED_LIBS Core Gui Widgets)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable(${PROJECT_NAME}
        main.cpp
        core/InputImage.cpp core/InputImage.h
        core/DoubleImage.cpp core/DoubleImage.h
        core/helper.h core/helper.cpp
        filter/FilterUtil.cpp filter/FilterUtil.h
        filter/Kernels.cpp filter/Kernels.h
        filter/border/IBorderPolicy.cpp filter/border/IBorderPolicy.h
        filter/border/MirrorPolicy.cpp filter/border/MirrorPolicy.h
        filter/border/ZeroPolicy.cpp filter/border/ZeroPolicy.h
        filter/border/SymmetryPolicy.cpp
        filter/border/SymmetryPolicy.h
        filter/border/CopyPolicy.cpp filter/border/CopyPolicy.h
        demonstration/Lab1.cpp demonstration/Lab1.h
        filter/border/Policies.cpp filter/border/Policies.h
        demonstration/Lab2.cpp demonstration/Lab2.h
        octave/OctavesCreator.cpp octave/OctavesCreator.h
        octave/OctaveElement.cpp octave/OctaveElement.h
        octave/Octave.cpp octave/Octave.h
        point/Point.cpp point/Point.h
        point/AbstractPointsFinder.cpp point/AbstractPointsFinder.h
        point/Moravec.cpp point/Moravec.h
        point/Harris.cpp point/Harris.h
        distortions/Distortion.cpp distortions/Distortion.h
        distortions/Contrast.cpp distortions/Contrast.h
        distortions/Rotate.cpp distortions/Rotate.h
        distortions/Scale.cpp distortions/Scale.h
        distortions/Shift.cpp distortions/Shift.h
        demonstration/Lab3.cpp demonstration/Lab3.h
        core/DoubleImageBorderPolicy.cpp core/DoubleImageBorderPolicy.h
        descriptor/AbstractDescriptor.cpp descriptor/AbstractDescriptor.h
        descriptor/PatchDescriptor.cpp descriptor/PatchDescriptor.h
        descriptor/PatchCreator.cpp descriptor/PatchCreator.h
        descriptor/DescriptorUtil.cpp descriptor/DescriptorUtil.h
        descriptor/MatchInfo.cpp descriptor/MatchInfo.h
        demonstration/Lab4.cpp demonstration/Lab4.cpp
        distortions/Noise.cpp distortions/Noise.h
        descriptor/HistogramDescriptor.cpp descriptor/HistogramDescriptor.h
        descriptor/SiftDescriptor.cpp descriptor/SiftDescriptor.h
        descriptor/Basket.cpp descriptor/Basket.h
        descriptor/HistogramCreator.cpp descriptor/HistogramCreator.h
        demonstration/Lab5.cpp demonstration/Lab5.h
        descriptor/SiftCreator.cpp descriptor/SiftCreator.h)

set(CMAKE_PREFIX_PATH /usr/include/{host}/qt{version}/)

if (NOT CMAKE_PREFIX_PATH)
    message(WARNING "CMAKE_PREFIX_PATH is not defined, you may need to set it "
            "(-DCMAKE_PREFIX_PATH=\"path/to/Qt/lib/cmake\" or -DCMAKE_PREFIX_PATH=/usr/include/{host}/qt{version}/ on Ubuntu)")
endif ()

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED})
