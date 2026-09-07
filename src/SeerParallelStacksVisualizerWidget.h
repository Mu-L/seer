// SPDX-FileCopyrightText: 2021 Ernie Pasveer <epasveer@att.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include "SeerParallelStacksCommon.h"
#include <QtWidgets/QWidget>
#include <QString>
#include "ui_SeerParallelStacksVisualizerWidget.h"

class SeerParallelStacksVisualizerWidget : public QWidget, protected Ui::SeerParallelStacksVisualizerWidgetForm {

    Q_OBJECT

    public:
        explicit SeerParallelStacksVisualizerWidget (QWidget* parent = 0);
       ~SeerParallelStacksVisualizerWidget ();

        void                        setSettings                         (const SeerParallelStacksSettings& settings);
        SeerParallelStacksSettings  settings                            () const;

        void                        setShowFullFunctionName             (bool flag);
        bool                        showFullFunctionName                () const;
        void                        setFunctionNameLength               (int length);
        int                         functionNameLength                  () const;
        void                        setShowMinimapMode                  (const QString& mode);
        const QString&              showMinimapMode                     () const;

    signals:
        void                        refreshParallelStackFrames          (int id);
        void                        selectedThread                      (int threadId);

    public slots:
        void                        refresh                             ();
        void                        handleText                          (const QString& text);

        // Another widget (e.g. the thread frames browser) selected a
        // thread — reflect it in the graph without re-announcing it via
        // selectedThread(), since that widget already told gdb itself.
        void                        handleThreadSelected                (int threadId);

        // Another widget (e.g. the stack frames browser) selected a frame —
        // reflect it in the graph the same way. The graph has no
        // frame-selection UI of its own, so there's no outgoing signal to
        // avoid re-announcing here.
        void                        handleFrameSelected                 (int frameLevel);

    protected slots:
        void                        handleRefreshButton                 ();
        void                        handleHelpButton                    ();
        void                        handlePrintButton                   ();
        void                        handleSaveButton                    ();
        void                        handleSettingsButton                ();
        void                        handleThemeChanged                  ();

    protected:
        void                        writeSettings                       ();
        void                        readSettings                        ();
        void                        resizeEvent                         (QResizeEvent* event);

    private:
        void                        createDirectedGraph                 ();

        int                         _id;
        SeerParallelStacksThreads   _threads;
        int                         _currentThreadId;
        int                         _currentFrameLevel;
        SeerParallelStacksSettings  _settings;
};

