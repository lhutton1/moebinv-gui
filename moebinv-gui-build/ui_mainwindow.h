/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dockwidget.h"
#include "view.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionSave;
    QAction *actionOpen;
    QAction *actionConfiguration;
    QAction *actionUser_Manual;
    QAction *actionAbout;
    QAction *actionCreate_Cycle;
    QAction *actionPan;
    QAction *actionLabels;
    QAction *actionzoomIn;
    QAction *actionzoomOut;
    QAction *actionDebug_bounding_rect;
    QAction *actionDefine_by_center_and_radius_squared;
    QAction *actionDefine_by_values;
    QAction *actionDefine_cycle;
    QAction *actionSave_As;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionDelete_cycle;
    QAction *actionSettings;
    QAction *actionFigure_Description;
    QAction *actionFloating;
    QAction *actionExact;
    QAction *actionQuit;
    QAction *actionProperties;
    QAction *actionPointMetric;
    QAction *actionCycleMetric;
    QAction *actionEllipticPointMetric;
    QAction *actionParabolicPointMetric;
    QAction *actionHyperbolicPointMetric;
    QAction *actionEllipticCycleMetric;
    QAction *actionParabolicCycleMetric;
    QAction *actionHyperbolicCycleMetric;
    QAction *actionEvaluationType;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    view *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuDefine_Cycle_2;
    QMenu *menuHelp;
    QMenu *menuView;
    QMenu *menuTools;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    dockWidget *dockWidgetRight;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QTreeView *treeView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1000, 600);
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionConfiguration = new QAction(MainWindow);
        actionConfiguration->setObjectName(QStringLiteral("actionConfiguration"));
        actionUser_Manual = new QAction(MainWindow);
        actionUser_Manual->setObjectName(QStringLiteral("actionUser_Manual"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionCreate_Cycle = new QAction(MainWindow);
        actionCreate_Cycle->setObjectName(QStringLiteral("actionCreate_Cycle"));
        actionPan = new QAction(MainWindow);
        actionPan->setObjectName(QStringLiteral("actionPan"));
        actionPan->setCheckable(true);
        actionLabels = new QAction(MainWindow);
        actionLabels->setObjectName(QStringLiteral("actionLabels"));
        actionLabels->setCheckable(true);
        actionzoomIn = new QAction(MainWindow);
        actionzoomIn->setObjectName(QStringLiteral("actionzoomIn"));
        actionzoomOut = new QAction(MainWindow);
        actionzoomOut->setObjectName(QStringLiteral("actionzoomOut"));
        actionDebug_bounding_rect = new QAction(MainWindow);
        actionDebug_bounding_rect->setObjectName(QStringLiteral("actionDebug_bounding_rect"));
        actionDebug_bounding_rect->setCheckable(true);
        actionDefine_by_center_and_radius_squared = new QAction(MainWindow);
        actionDefine_by_center_and_radius_squared->setObjectName(QStringLiteral("actionDefine_by_center_and_radius_squared"));
        actionDefine_by_values = new QAction(MainWindow);
        actionDefine_by_values->setObjectName(QStringLiteral("actionDefine_by_values"));
        actionDefine_cycle = new QAction(MainWindow);
        actionDefine_cycle->setObjectName(QStringLiteral("actionDefine_cycle"));
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName(QStringLiteral("actionSave_As"));
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName(QStringLiteral("actionUndo"));
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName(QStringLiteral("actionRedo"));
        actionDelete_cycle = new QAction(MainWindow);
        actionDelete_cycle->setObjectName(QStringLiteral("actionDelete_cycle"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        actionFigure_Description = new QAction(MainWindow);
        actionFigure_Description->setObjectName(QStringLiteral("actionFigure_Description"));
        actionFloating = new QAction(MainWindow);
        actionFloating->setObjectName(QStringLiteral("actionFloating"));
        actionFloating->setCheckable(true);
        actionExact = new QAction(MainWindow);
        actionExact->setObjectName(QStringLiteral("actionExact"));
        actionExact->setCheckable(true);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        actionProperties = new QAction(MainWindow);
        actionProperties->setObjectName(QStringLiteral("actionProperties"));
        actionPointMetric = new QAction(MainWindow);
        actionPointMetric->setObjectName(QStringLiteral("actionPointMetric"));
        actionCycleMetric = new QAction(MainWindow);
        actionCycleMetric->setObjectName(QStringLiteral("actionCycleMetric"));
        actionEllipticPointMetric = new QAction(MainWindow);
        actionEllipticPointMetric->setObjectName(QStringLiteral("actionEllipticPointMetric"));
        actionEllipticPointMetric->setCheckable(true);
        actionParabolicPointMetric = new QAction(MainWindow);
        actionParabolicPointMetric->setObjectName(QStringLiteral("actionParabolicPointMetric"));
        actionParabolicPointMetric->setCheckable(true);
        actionHyperbolicPointMetric = new QAction(MainWindow);
        actionHyperbolicPointMetric->setObjectName(QStringLiteral("actionHyperbolicPointMetric"));
        actionHyperbolicPointMetric->setCheckable(true);
        actionEllipticCycleMetric = new QAction(MainWindow);
        actionEllipticCycleMetric->setObjectName(QStringLiteral("actionEllipticCycleMetric"));
        actionEllipticCycleMetric->setCheckable(true);
        actionParabolicCycleMetric = new QAction(MainWindow);
        actionParabolicCycleMetric->setObjectName(QStringLiteral("actionParabolicCycleMetric"));
        actionParabolicCycleMetric->setCheckable(true);
        actionHyperbolicCycleMetric = new QAction(MainWindow);
        actionHyperbolicCycleMetric->setObjectName(QStringLiteral("actionHyperbolicCycleMetric"));
        actionHyperbolicCycleMetric->setCheckable(true);
        actionEvaluationType = new QAction(MainWindow);
        actionEvaluationType->setObjectName(QStringLiteral("actionEvaluationType"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new view(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(5);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setMouseTracking(true);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        graphicsView->setInteractive(true);
        graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::TextAntialiasing);
        graphicsView->setDragMode(QGraphicsView::NoDrag);

        horizontalLayout->addWidget(graphicsView);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 22));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuDefine_Cycle_2 = new QMenu(menuEdit);
        menuDefine_Cycle_2->setObjectName(QStringLiteral("menuDefine_Cycle_2"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        dockWidgetRight = new dockWidget(MainWindow);
        dockWidgetRight->setObjectName(QStringLiteral("dockWidgetRight"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dockWidgetRight->sizePolicy().hasHeightForWidth());
        dockWidgetRight->setSizePolicy(sizePolicy2);
        dockWidgetRight->setMinimumSize(QSize(200, 98));
        dockWidgetRight->setLayoutDirection(Qt::RightToLeft);
        dockWidgetRight->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        sizePolicy.setHeightForWidth(dockWidgetContents->sizePolicy().hasHeightForWidth());
        dockWidgetContents->setSizePolicy(sizePolicy);
        dockWidgetContents->setMinimumSize(QSize(200, 0));
        verticalLayout_2 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeView = new QTreeView(dockWidgetContents);
        treeView->setObjectName(QStringLiteral("treeView"));
        treeView->setLayoutDirection(Qt::LeftToRight);
        treeView->setStyleSheet(QStringLiteral(""));
        treeView->header()->setVisible(false);

        verticalLayout->addWidget(treeView);


        verticalLayout_2->addLayout(verticalLayout);

        dockWidgetRight->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidgetRight);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuEdit->addSeparator();
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addAction(actionDelete_cycle);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCreate_Cycle);
        menuEdit->addAction(menuDefine_Cycle_2->menuAction());
        menuEdit->addSeparator();
        menuEdit->addAction(actionEvaluationType);
        menuEdit->addAction(actionPointMetric);
        menuEdit->addAction(actionCycleMetric);
        menuEdit->addSeparator();
        menuEdit->addAction(actionProperties);
        menuDefine_Cycle_2->addAction(actionDefine_by_values);
        menuDefine_Cycle_2->addAction(actionDefine_by_center_and_radius_squared);
        menuHelp->addAction(actionUser_Manual);
        menuHelp->addAction(actionAbout);
        menuView->addAction(actionzoomIn);
        menuView->addAction(actionzoomOut);
        menuView->addAction(actionPan);
        menuView->addSeparator();
        menuView->addAction(actionLabels);
        menuView->addAction(actionDebug_bounding_rect);
        menuView->addSeparator();
        menuView->addAction(actionFigure_Description);
        menuView->addSeparator();
        menuTools->addAction(actionSettings);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "moebinv-gui", nullptr));
        actionNew->setText(QApplication::translate("MainWindow", "New", nullptr));
#ifndef QT_NO_SHORTCUT
        actionNew->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_NO_SHORTCUT
        actionSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionOpen->setText(QApplication::translate("MainWindow", "Open", nullptr));
#ifndef QT_NO_SHORTCUT
        actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_NO_SHORTCUT
        actionConfiguration->setText(QApplication::translate("MainWindow", "Configuration", nullptr));
        actionUser_Manual->setText(QApplication::translate("MainWindow", "User Manual...", nullptr));
        actionAbout->setText(QApplication::translate("MainWindow", "About...", nullptr));
        actionCreate_Cycle->setText(QApplication::translate("MainWindow", "Create Cycle", nullptr));
#ifndef QT_NO_TOOLTIP
        actionCreate_Cycle->setToolTip(QApplication::translate("MainWindow", "Create Cycle", nullptr));
#endif // QT_NO_TOOLTIP
        actionPan->setText(QApplication::translate("MainWindow", "Pan", nullptr));
#ifndef QT_NO_TOOLTIP
        actionPan->setToolTip(QApplication::translate("MainWindow", "Pan", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_SHORTCUT
        actionPan->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_NO_SHORTCUT
        actionLabels->setText(QApplication::translate("MainWindow", "Labels", nullptr));
        actionzoomIn->setText(QApplication::translate("MainWindow", "Zoom In", nullptr));
#ifndef QT_NO_SHORTCUT
        actionzoomIn->setShortcut(QApplication::translate("MainWindow", "Ctrl+]", nullptr));
#endif // QT_NO_SHORTCUT
        actionzoomOut->setText(QApplication::translate("MainWindow", "Zoom Out", nullptr));
#ifndef QT_NO_SHORTCUT
        actionzoomOut->setShortcut(QApplication::translate("MainWindow", "Ctrl+[", nullptr));
#endif // QT_NO_SHORTCUT
        actionDebug_bounding_rect->setText(QApplication::translate("MainWindow", "Debug bounding rect", nullptr));
        actionDefine_by_center_and_radius_squared->setText(QApplication::translate("MainWindow", "Define by center and radius squared...", nullptr));
        actionDefine_by_values->setText(QApplication::translate("MainWindow", "Define by values...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionDefine_by_values->setShortcut(QApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_NO_SHORTCUT
        actionDefine_cycle->setText(QApplication::translate("MainWindow", "Define Cycle", nullptr));
        actionSave_As->setText(QApplication::translate("MainWindow", "Save As", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSave_As->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", nullptr));
#endif // QT_NO_SHORTCUT
        actionUndo->setText(QApplication::translate("MainWindow", "Undo", nullptr));
#ifndef QT_NO_SHORTCUT
        actionUndo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actionRedo->setText(QApplication::translate("MainWindow", "Redo", nullptr));
#ifndef QT_NO_SHORTCUT
        actionRedo->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+Z", nullptr));
#endif // QT_NO_SHORTCUT
        actionDelete_cycle->setText(QApplication::translate("MainWindow", "Delete cycle...", nullptr));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings...", nullptr));
#ifndef QT_NO_SHORTCUT
        actionSettings->setShortcut(QApplication::translate("MainWindow", "Ctrl+,", nullptr));
#endif // QT_NO_SHORTCUT
        actionFigure_Description->setText(QApplication::translate("MainWindow", "Figure Description...", nullptr));
        actionFloating->setText(QApplication::translate("MainWindow", "Floating", nullptr));
        actionExact->setText(QApplication::translate("MainWindow", "Exact", nullptr));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", nullptr));
#ifndef QT_NO_SHORTCUT
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_NO_SHORTCUT
        actionProperties->setText(QApplication::translate("MainWindow", "Properties", nullptr));
#ifndef QT_NO_SHORTCUT
        actionProperties->setShortcut(QApplication::translate("MainWindow", "Ctrl+P", nullptr));
#endif // QT_NO_SHORTCUT
        actionPointMetric->setText(QApplication::translate("MainWindow", "Point Metric", nullptr));
        actionCycleMetric->setText(QApplication::translate("MainWindow", "Cycle Metric", nullptr));
        actionEllipticPointMetric->setText(QApplication::translate("MainWindow", "Elliptic", nullptr));
        actionParabolicPointMetric->setText(QApplication::translate("MainWindow", "Parabolic", nullptr));
        actionHyperbolicPointMetric->setText(QApplication::translate("MainWindow", "Hyperbolic", nullptr));
        actionEllipticCycleMetric->setText(QApplication::translate("MainWindow", "Elliptic", nullptr));
        actionParabolicCycleMetric->setText(QApplication::translate("MainWindow", "Parabolic", nullptr));
        actionHyperbolicCycleMetric->setText(QApplication::translate("MainWindow", "Hyperbolic", nullptr));
        actionEvaluationType->setText(QApplication::translate("MainWindow", "Evaluation Type", nullptr));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", nullptr));
        menuDefine_Cycle_2->setTitle(QApplication::translate("MainWindow", "Define Cycle", nullptr));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", nullptr));
        menuView->setTitle(QApplication::translate("MainWindow", "View", nullptr));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
