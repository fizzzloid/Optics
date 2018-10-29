/********************************************************************************
** Form generated from reading UI file 'optic_options.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIC_OPTIONS_H
#define UI_OPTIC_OPTIONS_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_optic_options
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_8;
    QDial *angle_dial;
    QDoubleSpinBox *angle_spin;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout;
    QPushButton *ccv_btn;
    QPushButton *up_btn;
    QPushButton *cv_btn;
    QPushButton *left_btn;
    QPushButton *down_btn;
    QPushButton *right_btn;
    QHBoxLayout *horizontalLayout_3;
    QDoubleSpinBox *x_spin;
    QDoubleSpinBox *y_spin;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *outline_color_btn;
    QPushButton *material_color_btn;
    QVBoxLayout *verticalLayout_5;
    QDoubleSpinBox *outline_opacity_spin;
    QDoubleSpinBox *material_opacity_spin;
    QVBoxLayout *verticalLayout_6;
    QLabel *outline_color_preview;
    QLabel *material_color_preview;
    QVBoxLayout *verticalLayout;
    QDialogButtonBox *buttonBox;
    QPushButton *delete_btn;
    QPushButton *reset_btn;

    void setupUi(QDialog *optic_options)
    {
        if (optic_options->objectName().isEmpty())
            optic_options->setObjectName(QStringLiteral("optic_options"));
        optic_options->resize(559, 356);
        horizontalLayout = new QHBoxLayout(optic_options);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        groupBox_2 = new QGroupBox(optic_options);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        angle_dial = new QDial(groupBox_2);
        angle_dial->setObjectName(QStringLiteral("angle_dial"));
        angle_dial->setMaximum(359);
        angle_dial->setSliderPosition(90);
        angle_dial->setInvertedAppearance(true);
        angle_dial->setWrapping(true);
        angle_dial->setNotchTarget(45);
        angle_dial->setNotchesVisible(true);

        verticalLayout_8->addWidget(angle_dial);

        angle_spin = new QDoubleSpinBox(groupBox_2);
        angle_spin->setObjectName(QStringLiteral("angle_spin"));
        angle_spin->setDecimals(2);
        angle_spin->setMinimum(-1);
        angle_spin->setMaximum(360);
        angle_spin->setSingleStep(0.5);

        verticalLayout_8->addWidget(angle_spin);


        horizontalLayout_4->addLayout(verticalLayout_8);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        ccv_btn = new QPushButton(groupBox_2);
        ccv_btn->setObjectName(QStringLiteral("ccv_btn"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ccv_btn->sizePolicy().hasHeightForWidth());
        ccv_btn->setSizePolicy(sizePolicy);
        ccv_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(ccv_btn, 0, 0, 1, 1);

        up_btn = new QPushButton(groupBox_2);
        up_btn->setObjectName(QStringLiteral("up_btn"));
        sizePolicy.setHeightForWidth(up_btn->sizePolicy().hasHeightForWidth());
        up_btn->setSizePolicy(sizePolicy);
        up_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(up_btn, 0, 1, 1, 1);

        cv_btn = new QPushButton(groupBox_2);
        cv_btn->setObjectName(QStringLiteral("cv_btn"));
        sizePolicy.setHeightForWidth(cv_btn->sizePolicy().hasHeightForWidth());
        cv_btn->setSizePolicy(sizePolicy);
        cv_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(cv_btn, 0, 2, 1, 1);

        left_btn = new QPushButton(groupBox_2);
        left_btn->setObjectName(QStringLiteral("left_btn"));
        sizePolicy.setHeightForWidth(left_btn->sizePolicy().hasHeightForWidth());
        left_btn->setSizePolicy(sizePolicy);
        left_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(left_btn, 1, 0, 1, 1);

        down_btn = new QPushButton(groupBox_2);
        down_btn->setObjectName(QStringLiteral("down_btn"));
        sizePolicy.setHeightForWidth(down_btn->sizePolicy().hasHeightForWidth());
        down_btn->setSizePolicy(sizePolicy);
        down_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(down_btn, 1, 1, 1, 1);

        right_btn = new QPushButton(groupBox_2);
        right_btn->setObjectName(QStringLiteral("right_btn"));
        sizePolicy.setHeightForWidth(right_btn->sizePolicy().hasHeightForWidth());
        right_btn->setSizePolicy(sizePolicy);
        right_btn->setMaximumSize(QSize(70, 70));

        gridLayout->addWidget(right_btn, 1, 2, 1, 1);


        verticalLayout_7->addLayout(gridLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        x_spin = new QDoubleSpinBox(groupBox_2);
        x_spin->setObjectName(QStringLiteral("x_spin"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(x_spin->sizePolicy().hasHeightForWidth());
        x_spin->setSizePolicy(sizePolicy1);
        x_spin->setDecimals(4);
        x_spin->setMinimum(-1e+10);
        x_spin->setMaximum(1e+10);
        x_spin->setSingleStep(0.001);

        horizontalLayout_3->addWidget(x_spin);

        y_spin = new QDoubleSpinBox(groupBox_2);
        y_spin->setObjectName(QStringLiteral("y_spin"));
        sizePolicy1.setHeightForWidth(y_spin->sizePolicy().hasHeightForWidth());
        y_spin->setSizePolicy(sizePolicy1);
        y_spin->setDecimals(4);
        y_spin->setMinimum(-1e+10);
        y_spin->setMaximum(1e+10);
        y_spin->setSingleStep(0.001);
        y_spin->setValue(0);

        horizontalLayout_3->addWidget(y_spin);


        verticalLayout_7->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_7);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox = new QGroupBox(optic_options);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_2);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        outline_color_btn = new QPushButton(groupBox);
        outline_color_btn->setObjectName(QStringLiteral("outline_color_btn"));

        verticalLayout_4->addWidget(outline_color_btn);

        material_color_btn = new QPushButton(groupBox);
        material_color_btn->setObjectName(QStringLiteral("material_color_btn"));

        verticalLayout_4->addWidget(material_color_btn);


        horizontalLayout_2->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        outline_opacity_spin = new QDoubleSpinBox(groupBox);
        outline_opacity_spin->setObjectName(QStringLiteral("outline_opacity_spin"));
        outline_opacity_spin->setMaximum(1);
        outline_opacity_spin->setSingleStep(0.05);
        outline_opacity_spin->setValue(1);

        verticalLayout_5->addWidget(outline_opacity_spin);

        material_opacity_spin = new QDoubleSpinBox(groupBox);
        material_opacity_spin->setObjectName(QStringLiteral("material_opacity_spin"));
        material_opacity_spin->setMaximum(1);
        material_opacity_spin->setSingleStep(0.05);
        material_opacity_spin->setValue(1);

        verticalLayout_5->addWidget(material_opacity_spin);


        horizontalLayout_2->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        outline_color_preview = new QLabel(groupBox);
        outline_color_preview->setObjectName(QStringLiteral("outline_color_preview"));
        outline_color_preview->setMinimumSize(QSize(40, 40));
        outline_color_preview->setAutoFillBackground(true);
        outline_color_preview->setFrameShape(QFrame::Box);
        outline_color_preview->setText(QStringLiteral(""));

        verticalLayout_6->addWidget(outline_color_preview);

        material_color_preview = new QLabel(groupBox);
        material_color_preview->setObjectName(QStringLiteral("material_color_preview"));
        material_color_preview->setMinimumSize(QSize(40, 40));
        material_color_preview->setAutoFillBackground(true);
        material_color_preview->setFrameShape(QFrame::Box);
        material_color_preview->setFrameShadow(QFrame::Plain);
        material_color_preview->setText(QStringLiteral(""));

        verticalLayout_6->addWidget(material_color_preview);


        horizontalLayout_2->addLayout(verticalLayout_6);


        verticalLayout_2->addWidget(groupBox);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinimumSize);
        buttonBox = new QDialogButtonBox(optic_options);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        delete_btn = new QPushButton(optic_options);
        delete_btn->setObjectName(QStringLiteral("delete_btn"));

        verticalLayout->addWidget(delete_btn);

        reset_btn = new QPushButton(optic_options);
        reset_btn->setObjectName(QStringLiteral("reset_btn"));

        verticalLayout->addWidget(reset_btn);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(optic_options);
        QObject::connect(buttonBox, SIGNAL(accepted()), optic_options, SLOT(accept()));

        QMetaObject::connectSlotsByName(optic_options);
    } // setupUi

    void retranslateUi(QDialog *optic_options)
    {
        optic_options->setWindowTitle(QApplication::translate("optic_options", "Dialog", nullptr));
        groupBox_2->setTitle(QApplication::translate("optic_options", "&Geometry", nullptr));
        angle_spin->setSuffix(QApplication::translate("optic_options", "\302\260", nullptr));
        ccv_btn->setText(QApplication::translate("optic_options", "CCV (Q)", nullptr));
#ifndef QT_NO_SHORTCUT
        ccv_btn->setShortcut(QApplication::translate("optic_options", "Q", nullptr));
#endif // QT_NO_SHORTCUT
        up_btn->setText(QApplication::translate("optic_options", "Up (W)", nullptr));
#ifndef QT_NO_SHORTCUT
        up_btn->setShortcut(QApplication::translate("optic_options", "W", nullptr));
#endif // QT_NO_SHORTCUT
        cv_btn->setText(QApplication::translate("optic_options", "CV (E)", nullptr));
#ifndef QT_NO_SHORTCUT
        cv_btn->setShortcut(QApplication::translate("optic_options", "E", nullptr));
#endif // QT_NO_SHORTCUT
        left_btn->setText(QApplication::translate("optic_options", "Left (A)", nullptr));
#ifndef QT_NO_SHORTCUT
        left_btn->setShortcut(QApplication::translate("optic_options", "A", nullptr));
#endif // QT_NO_SHORTCUT
        down_btn->setText(QApplication::translate("optic_options", "Down (S)", nullptr));
#ifndef QT_NO_SHORTCUT
        down_btn->setShortcut(QApplication::translate("optic_options", "S", nullptr));
#endif // QT_NO_SHORTCUT
        right_btn->setText(QApplication::translate("optic_options", "Right", nullptr));
#ifndef QT_NO_SHORTCUT
        right_btn->setShortcut(QApplication::translate("optic_options", "R", nullptr));
#endif // QT_NO_SHORTCUT
        x_spin->setPrefix(QApplication::translate("optic_options", "x = ", nullptr));
        y_spin->setPrefix(QApplication::translate("optic_options", "y = ", nullptr));
        groupBox->setTitle(QApplication::translate("optic_options", "&Color", nullptr));
        label->setText(QApplication::translate("optic_options", "Outline", nullptr));
        label_2->setText(QApplication::translate("optic_options", "Material", nullptr));
        outline_color_btn->setText(QApplication::translate("optic_options", "Select color", nullptr));
        material_color_btn->setText(QApplication::translate("optic_options", "Select color", nullptr));
        delete_btn->setText(QApplication::translate("optic_options", "&Delete", nullptr));
        reset_btn->setText(QApplication::translate("optic_options", "&Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class optic_options: public Ui_optic_options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIC_OPTIONS_H
