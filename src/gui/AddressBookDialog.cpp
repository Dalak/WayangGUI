// Copyright (c) 2011-2017 The Cryptonote developers
// Copyright (c) 2014-2017 XDN developers
// Copyright (c) 2016-2017 BXC developers
// Copyright (c) 2017 Royalties developers
// Copyright (c) 2017 Wayang developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "AddressBookDialog.h"
#include "AddressBookModel.h"

#include "ui_addressbookdialog.h"

namespace WalletGui {

AddressBookDialog::AddressBookDialog(QWidget* _parent) : QDialog(_parent), m_ui(new Ui::AddressBookDialog) {
  m_ui->setupUi(this);
  m_ui->m_addressBookView->setModel(&AddressBookModel::instance());
  if (AddressBookModel::instance().rowCount() > 0) {
    m_ui->m_addressBookView->setCurrentIndex(AddressBookModel::instance().index(0, 0));
  }
}

AddressBookDialog::~AddressBookDialog() {
}

QString AddressBookDialog::getAddress() const {
  return m_ui->m_addressBookView->currentIndex().data(AddressBookModel::ROLE_ADDRESS).toString();
}

}
