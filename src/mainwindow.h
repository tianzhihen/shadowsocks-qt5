/*
 * MainWindow class
 * Lots of variables, functions are included in this class
 * Copyright 2014-2015 Symeon Huang <hzwhuang@gmail.com>
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include "confighelper.h"

#ifdef UBUNTU_UNITY
#undef signals
extern "C"
{
#include <libappindicator/app-indicator.h>
#include <gtk/gtk.h>
}
#define signals public
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool isOnlyOneInstance() const;
    bool isHideWindowOnStartup() const;
    bool isUsingAppIndicator() const;

public slots:
    void minimizeToSysTray();
    void onShowSignalRecv();

private:
    ConfigHelper *configHelper;
    QMenu *systrayMenu;
    QSystemTrayIcon *systray;
    Ui::MainWindow *ui;
#ifdef UBUNTU_UNITY
    GtkWidget *showItem;
#endif

    bool useAppIndicator;

    void newProfile(Connection *);
    void editRow(int row);
    void createSystemTray();
    void createAppIndicator();
    void blockChildrenSignals(bool);

    //desktop environments that need application indicator
    static const QStringList appIndicatorDE;
    static const QUrl issueUrl;

private slots:
    void onImportGuiJson();
    void onAddManually();
    void onAddScreenQRCode();
    void onAddQRCodeFile();
    void onAddFromURI();
    void onAddFromConfigJSON();
    void onDelete();
    void onEdit();
    void onDoubleClicked(const QModelIndex &index);
    void onShare();
    void onConnect();
    void onDisconnect();
    void onConnectionStatusChanged(const int row, const bool running);
    void onLatencyTest();
    void onViewLog();
    void onStatus();
    void onMoveUp();
    void onMoveDown();
    void onGeneralSettings();
    void checkCurrentIndex(const QModelIndex &index);
    void showNotification(const QString &);
    void showWindow();
    void onSystrayActivated(QSystemTrayIcon::ActivationReason);
    void onAbout();
    void onReportBug();
    void onCustomContextMenuRequested(const QPoint &pos);

protected:
    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
