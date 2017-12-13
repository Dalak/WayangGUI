// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2017 Wayang developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H
#pragma once

#include <QDialog>

namespace Ui {
class AboutDialog;
}

namespace WalletGui {

/** "About" dialog box */
class AboutDialog : public QDialog
{
    Q_OBJECT
    Q_DISABLE_COPY(AboutDialog)

public:
    explicit AboutDialog(QWidget *parent = 0);
    ~AboutDialog();

private:
    Ui::AboutDialog *m_ui;

private slots:
    void on_m_OkButton_accepted();
};

}

#endif // ABOUTDIALOG_H
