/**********************************************************************
            --- KDevelop (KDlgEdit)  generated file ---

            Last generated: Fri Jul 14 12:52:10 2000

            DO NOT EDIT!!!  This file will be automatically
            regenerated by KDevelop.  All changes will be lost.

**********************************************************************/
#include "cselectgamedlg.h"
#include <QGridLayout>

void CSelectGameDlg::initDialog()
{
    QGridLayout *grid = new QGridLayout(this);

    QPushButton_1 = new QPushButton(this);
    QPushButton_1->setText("OK");
    grid->addWidget(QPushButton_1, 1, 1);

    QLabel_1 = new QLabel(this);
    QLabel_1->setText("Game:");
    grid->addWidget(QLabel_1, 0, 0);

    QSpinBox_1 = new QSpinBox(this);
    QSpinBox_1->setRange(1, 50000);
    grid->addWidget(QSpinBox_1, 0, 1);

    QPushButton_ABORT = new QPushButton(this);
    QPushButton_ABORT->setText("Abort");
    grid->addWidget(QPushButton_ABORT, 1, 0);
}
