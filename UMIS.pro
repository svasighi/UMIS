QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    dbmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    students/assessmentform.cpp \
    students/changepasswordform.cpp \
    students/enrolltimeform.cpp \
    students/examscheduleform.cpp \
    students/fullinformationform.cpp \
    students/mainenrollmentform.cpp \
    students/prepenrollmentform.cpp \
    students/presentedcoursesform.cpp \
    students/studentwindow.cpp \
    students/tuitionform.cpp \
    students/weekscheduleform.cpp \
    professors/professorwindow.cpp \
    professors/professorpresentedcoursesform.cpp \
    professors/professorslistform.cpp\
    src/user.cpp \
    src/student.cpp \
    src/TimeDate.cpp \
    src/EnrollmentError.cpp \
    src/AcademicAffairs.cpp \
    src/Professor.cpp \
    src/course.cpp

HEADERS += \
    dbmanager.h \
    mainwindow.h \
    students/assessmentform.h \
    students/changepasswordform.h \
    students/enrolltimeform.h \
    students/examscheduleform.h \
    students/fullinformationform.h \
    students/mainenrollmentform.h \
    students/prepenrollmentform.h \
    students/presentedcoursesform.h \
    students/studentwindow.h \
    students/tuitionform.h \
    students/weekscheduleform.h \
    professors/professorpresentedcoursesform.h \
    professors/professorslistform.h \
    professors/professorwindow.h \
    src/student.h \
    src/user.h \
    src/TimeDate.h \
    src/EnrollmentError.h \
    src/AcademicAffairs.h \
    src/course.h \
    src/professor.h \
    variables.h

FORMS += \
    mainwindow.ui \
    students/assessmentform.ui \
    students/changepasswordform.ui \
    students/enrolltimeform.ui \
    students/examscheduleform.ui \
    students/fullinformationform.ui \
    students/mainenrollmentform.ui \
    students/prepenrollmentform.ui \
    students/presentedcoursesform.ui \
    students/studentwindow.ui \
    students/tuitionform.ui \
    students/weekscheduleform.ui \
    professors/professorpresentedcoursesform.ui \
    professors/professorslistform.ui \
    professors/professorwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
