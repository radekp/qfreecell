/**********************************************************************
            --- KDevelop (KDlgEdit)  generated file ---                

            Last generated: Fri Jul 14 13:55:26 2000

            DO NOT EDIT!!!  This file will be automatically
            regenerated by KDevelop.  All changes will be lost.

**********************************************************************/
#include "cstatistics.h"
#include <QGridLayout>

void CStatistics::initDialog()
{
    QGridLayout *grid = new QGridLayout(this);

    QLabel_1 = new QLabel(this);
    QLabel_1->setText("Won:");
    grid->addWidget(QLabel_1, 0, 0);

    QLabel_WonAll = new QLabel(this);
    QLabel_WonAll->setText("0");
    grid->addWidget(QLabel_WonAll, 0, 1);

    QLabel_WonAllPercent = new QLabel(this);
    QLabel_WonAllPercent->setText("0%");
    grid->addWidget(QLabel_WonAllPercent, 0, 2);

    QLabel_2 = new QLabel(this);
    QLabel_2->setText("Lost:");
    grid->addWidget(QLabel_2, 1, 0);

    QLabel_LostAll = new QLabel(this);
    QLabel_LostAll->setText("0");
    grid->addWidget(QLabel_LostAll, 1, 1);

    QLabel_3 = new QLabel(this);
    QLabel_3->setText("This session");
    grid->addWidget(QLabel_3, 2, 0);

    QLabel_4 = new QLabel(this);
    QLabel_4->setText("Won:");
    grid->addWidget(QLabel_4, 3, 0);

    QLabel_WonSession = new QLabel(this);
    QLabel_WonSession->setText("0");
    grid->addWidget(QLabel_WonSession, 3, 1);

    QLabel_WonSessionPercent = new QLabel(this);
    QLabel_WonSessionPercent->setText("0%");
    grid->addWidget(QLabel_WonSessionPercent, 3, 2);

    QLabel_LostSession = new QLabel(this);
    QLabel_LostSession->setText("0");
    grid->addWidget(QLabel_LostSession, 3, 2);

    QLabel_5 = new QLabel(this);
    QLabel_5->setText("Lost:");
    grid->addWidget(QLabel_5, 4, 0);

    QPushButton_OK = new QPushButton(this);
    QPushButton_OK->setText("OK");
    grid->addWidget(QPushButton_OK, 5, 0);

    QPushButton_RESET = new QPushButton(this);
    QPushButton_RESET->setText("Reset");

    grid->addWidget(QPushButton_RESET, 5, 1);
}
