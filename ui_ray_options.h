/********************************************************************************
** Form generated from reading UI file 'ray_options.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAY_OPTIONS_H
#define UI_RAY_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ray_options
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *angle_groupbox;
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QDial *angle_dial;
    QDoubleSpinBox *angle_spinbox;
    QVBoxLayout *verticalLayout_6;
    QGridLayout *gridLayout;
    QPushButton *right_btn;
    QPushButton *up_btn;
    QPushButton *left_btn;
    QPushButton *down_btn;
    QPushButton *ccv_btn;
    QPushButton *cv_btn;
    QHBoxLayout *horizontalLayout_8;
    QDoubleSpinBox *x_spin_box;
    QDoubleSpinBox *y_spin_box;
    QGroupBox *color_group_box;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *red_label;
    QLabel *green_label;
    QLabel *blue_label;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QSlider *red_slider;
    QSpinBox *red_spinBox;
    QHBoxLayout *horizontalLayout_5;
    QSlider *green_slider;
    QSpinBox *green_spinBox;
    QHBoxLayout *horizontalLayout_6;
    QSlider *blue_slider;
    QSpinBox *blue_spinBox;
    QLabel *color_preview;
    QVBoxLayout *verticalLayout_4;
    QDialogButtonBox *buttonBox;
    QPushButton *delete_button;
    QPushButton *reset_btn;

    void setupUi(QDialog *ray_options)
    {
        if (ray_options->objectName().isEmpty())
            ray_options->setObjectName(QStringLiteral("ray_options"));
        ray_options->resize(440, 364);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ray_options->sizePolicy().hasHeightForWidth());
        ray_options->setSizePolicy(sizePolicy);
        ray_options->setMinimumSize(QSize(440, 340));
        horizontalLayout = new QHBoxLayout(ray_options);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        angle_groupbox = new QGroupBox(ray_options);
        angle_groupbox->setObjectName(QStringLiteral("angle_groupbox"));
        horizontalLayout_7 = new QHBoxLayout(angle_groupbox);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        angle_dial = new QDial(angle_groupbox);
        angle_dial->setObjectName(QStringLiteral("angle_dial"));
        angle_dial->setLayoutDirection(Qt::LeftToRight);
        angle_dial->setAutoFillBackground(false);
        angle_dial->setMaximum(359);
        angle_dial->setSingleStep(1);
        angle_dial->setPageStep(10);
        angle_dial->setSliderPosition(90);
        angle_dial->setOrientation(Qt::Horizontal);
        angle_dial->setInvertedAppearance(true);
        angle_dial->setInvertedControls(false);
        angle_dial->setWrapping(true);
        angle_dial->setNotchTarget(45);
        angle_dial->setNotchesVisible(true);

        verticalLayout_2->addWidget(angle_dial);

        angle_spinbox = new QDoubleSpinBox(angle_groupbox);
        angle_spinbox->setObjectName(QStringLiteral("angle_spinbox"));
        sizePolicy.setHeightForWidth(angle_spinbox->sizePolicy().hasHeightForWidth());
        angle_spinbox->setSizePolicy(sizePolicy);
        angle_spinbox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        angle_spinbox->setSuffix(QString::fromUtf8("\302\260"));
        angle_spinbox->setMinimum(-1);
        angle_spinbox->setMaximum(360);
        angle_spinbox->setSingleStep(0.1);

        verticalLayout_2->addWidget(angle_spinbox);


        horizontalLayout_7->addLayout(verticalLayout_2);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setSizeConstraint(QLayout::SetMaximumSize);
        right_btn = new QPushButton(angle_groupbox);
        right_btn->setObjectName(QStringLiteral("right_btn"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(right_btn->sizePolicy().hasHeightForWidth());
        right_btn->setSizePolicy(sizePolicy1);
        right_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(right_btn, 1, 2, 1, 1);

        up_btn = new QPushButton(angle_groupbox);
        up_btn->setObjectName(QStringLiteral("up_btn"));
        sizePolicy1.setHeightForWidth(up_btn->sizePolicy().hasHeightForWidth());
        up_btn->setSizePolicy(sizePolicy1);
        up_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(up_btn, 0, 1, 1, 1);

        left_btn = new QPushButton(angle_groupbox);
        left_btn->setObjectName(QStringLiteral("left_btn"));
        sizePolicy1.setHeightForWidth(left_btn->sizePolicy().hasHeightForWidth());
        left_btn->setSizePolicy(sizePolicy1);
        left_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(left_btn, 1, 0, 1, 1);

        down_btn = new QPushButton(angle_groupbox);
        down_btn->setObjectName(QStringLiteral("down_btn"));
        down_btn->setEnabled(true);
        sizePolicy1.setHeightForWidth(down_btn->sizePolicy().hasHeightForWidth());
        down_btn->setSizePolicy(sizePolicy1);
        down_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(down_btn, 1, 1, 1, 1);

        ccv_btn = new QPushButton(angle_groupbox);
        ccv_btn->setObjectName(QStringLiteral("ccv_btn"));
        sizePolicy1.setHeightForWidth(ccv_btn->sizePolicy().hasHeightForWidth());
        ccv_btn->setSizePolicy(sizePolicy1);
        ccv_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(ccv_btn, 0, 0, 1, 1);

        cv_btn = new QPushButton(angle_groupbox);
        cv_btn->setObjectName(QStringLiteral("cv_btn"));
        sizePolicy1.setHeightForWidth(cv_btn->sizePolicy().hasHeightForWidth());
        cv_btn->setSizePolicy(sizePolicy1);
        cv_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(cv_btn, 0, 2, 1, 1);


        verticalLayout_6->addLayout(gridLayout);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        x_spin_box = new QDoubleSpinBox(angle_groupbox);
        x_spin_box->setObjectName(QStringLiteral("x_spin_box"));
        sizePolicy.setHeightForWidth(x_spin_box->sizePolicy().hasHeightForWidth());
        x_spin_box->setSizePolicy(sizePolicy);
        x_spin_box->setDecimals(4);
        x_spin_box->setMinimum(-1e+10);
        x_spin_box->setMaximum(1e+10);
        x_spin_box->setSingleStep(0.001);

        horizontalLayout_8->addWidget(x_spin_box);

        y_spin_box = new QDoubleSpinBox(angle_groupbox);
        y_spin_box->setObjectName(QStringLiteral("y_spin_box"));
        sizePolicy.setHeightForWidth(y_spin_box->sizePolicy().hasHeightForWidth());
        y_spin_box->setSizePolicy(sizePolicy);
        y_spin_box->setDecimals(4);
        y_spin_box->setMinimum(-1e+10);
        y_spin_box->setMaximum(1e+10);
        y_spin_box->setSingleStep(0.001);

        horizontalLayout_8->addWidget(y_spin_box);


        verticalLayout_6->addLayout(horizontalLayout_8);


        horizontalLayout_7->addLayout(verticalLayout_6);


        verticalLayout->addWidget(angle_groupbox);

        color_group_box = new QGroupBox(ray_options);
        color_group_box->setObjectName(QStringLiteral("color_group_box"));
        horizontalLayout_3 = new QHBoxLayout(color_group_box);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        red_label = new QLabel(color_group_box);
        red_label->setObjectName(QStringLiteral("red_label"));
        red_label->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(red_label);

        green_label = new QLabel(color_group_box);
        green_label->setObjectName(QStringLiteral("green_label"));
        green_label->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(green_label);

        blue_label = new QLabel(color_group_box);
        blue_label->setObjectName(QStringLiteral("blue_label"));
        blue_label->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(blue_label);


        horizontalLayout_3->addLayout(verticalLayout_5);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        red_slider = new QSlider(color_group_box);
        red_slider->setObjectName(QStringLiteral("red_slider"));
        red_slider->setMaximum(255);
        red_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(red_slider);

        red_spinBox = new QSpinBox(color_group_box);
        red_spinBox->setObjectName(QStringLiteral("red_spinBox"));
        red_spinBox->setMaximum(255);

        horizontalLayout_4->addWidget(red_spinBox);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        green_slider = new QSlider(color_group_box);
        green_slider->setObjectName(QStringLiteral("green_slider"));
        green_slider->setMaximum(255);
        green_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(green_slider);

        green_spinBox = new QSpinBox(color_group_box);
        green_spinBox->setObjectName(QStringLiteral("green_spinBox"));
        green_spinBox->setMaximum(255);

        horizontalLayout_5->addWidget(green_spinBox);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        blue_slider = new QSlider(color_group_box);
        blue_slider->setObjectName(QStringLiteral("blue_slider"));
        blue_slider->setMaximum(255);
        blue_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(blue_slider);

        blue_spinBox = new QSpinBox(color_group_box);
        blue_spinBox->setObjectName(QStringLiteral("blue_spinBox"));
        blue_spinBox->setMaximum(255);

        horizontalLayout_6->addWidget(blue_spinBox);


        verticalLayout_3->addLayout(horizontalLayout_6);


        horizontalLayout_3->addLayout(verticalLayout_3);

        color_preview = new QLabel(color_group_box);
        color_preview->setObjectName(QStringLiteral("color_preview"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(color_preview->sizePolicy().hasHeightForWidth());
        color_preview->setSizePolicy(sizePolicy2);
        color_preview->setMinimumSize(QSize(30, 30));
        color_preview->setSizeIncrement(QSize(0, 0));
        color_preview->setAutoFillBackground(true);
        color_preview->setFrameShape(QFrame::Box);
        color_preview->setMidLineWidth(0);

        horizontalLayout_3->addWidget(color_preview);


        verticalLayout->addWidget(color_group_box);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        buttonBox = new QDialogButtonBox(ray_options);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(buttonBox);

        delete_button = new QPushButton(ray_options);
        delete_button->setObjectName(QStringLiteral("delete_button"));

        verticalLayout_4->addWidget(delete_button);

        reset_btn = new QPushButton(ray_options);
        reset_btn->setObjectName(QStringLiteral("reset_btn"));

        verticalLayout_4->addWidget(reset_btn);


        horizontalLayout->addLayout(verticalLayout_4);

#ifndef QT_NO_SHORTCUT
        red_label->setBuddy(red_slider);
        green_label->setBuddy(green_slider);
        blue_label->setBuddy(blue_slider);
#endif // QT_NO_SHORTCUT

        retranslateUi(ray_options);
        QObject::connect(blue_slider, SIGNAL(valueChanged(int)), blue_spinBox, SLOT(setValue(int)));
        QObject::connect(green_slider, SIGNAL(valueChanged(int)), green_spinBox, SLOT(setValue(int)));
        QObject::connect(green_spinBox, SIGNAL(valueChanged(int)), green_slider, SLOT(setValue(int)));
        QObject::connect(red_slider, SIGNAL(valueChanged(int)), red_spinBox, SLOT(setValue(int)));
        QObject::connect(red_spinBox, SIGNAL(valueChanged(int)), red_slider, SLOT(setValue(int)));
        QObject::connect(buttonBox, SIGNAL(accepted()), ray_options, SLOT(accept()));
        QObject::connect(blue_spinBox, SIGNAL(valueChanged(int)), blue_slider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(ray_options);
    } // setupUi

    void retranslateUi(QDialog *ray_options)
    {
        ray_options->setWindowTitle(QApplication::translate("ray_options", "Ray's options", nullptr));
        angle_groupbox->setTitle(QApplication::translate("ray_options", "&Geometry", nullptr));
        right_btn->setText(QApplication::translate("ray_options", "Right (D)", nullptr));
#ifndef QT_NO_SHORTCUT
        right_btn->setShortcut(QApplication::translate("ray_options", "D", nullptr));
#endif // QT_NO_SHORTCUT
        up_btn->setText(QApplication::translate("ray_options", "Up (W)", nullptr));
#ifndef QT_NO_SHORTCUT
        up_btn->setShortcut(QApplication::translate("ray_options", "W", nullptr));
#endif // QT_NO_SHORTCUT
        left_btn->setText(QApplication::translate("ray_options", "Left (A)", nullptr));
#ifndef QT_NO_SHORTCUT
        left_btn->setShortcut(QApplication::translate("ray_options", "A", nullptr));
#endif // QT_NO_SHORTCUT
        down_btn->setText(QApplication::translate("ray_options", "Down (S)", nullptr));
#ifndef QT_NO_SHORTCUT
        down_btn->setShortcut(QApplication::translate("ray_options", "S", nullptr));
#endif // QT_NO_SHORTCUT
        ccv_btn->setText(QApplication::translate("ray_options", "CCV (Q)", nullptr));
#ifndef QT_NO_SHORTCUT
        ccv_btn->setShortcut(QApplication::translate("ray_options", "Q", nullptr));
#endif // QT_NO_SHORTCUT
        cv_btn->setText(QApplication::translate("ray_options", "CV (E)", nullptr));
#ifndef QT_NO_SHORTCUT
        cv_btn->setShortcut(QApplication::translate("ray_options", "E", nullptr));
#endif // QT_NO_SHORTCUT
        x_spin_box->setPrefix(QApplication::translate("ray_options", "x = ", nullptr));
        y_spin_box->setPrefix(QApplication::translate("ray_options", "y = ", nullptr));
        color_group_box->setTitle(QApplication::translate("ray_options", "&Color", nullptr));
        red_label->setText(QApplication::translate("ray_options", "&Red", nullptr));
        green_label->setText(QApplication::translate("ray_options", "&Green", nullptr));
        blue_label->setText(QApplication::translate("ray_options", "&Blue", nullptr));
        color_preview->setText(QString());
        delete_button->setText(QApplication::translate("ray_options", "Delete", nullptr));
        reset_btn->setText(QApplication::translate("ray_options", "&Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ray_options: public Ui_ray_options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAY_OPTIONS_H
