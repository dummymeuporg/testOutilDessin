#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>
#include <QScrollArea>

#include <chipsetcell.h>
#include <mapcell.h>

class FenPrincipale : public QMainWindow
{
    Q_OBJECT

    public:
    FenPrincipale();

    public slots:
    void receptionCoord(int coordX, int coordY);
    void receptionEtatSouris(bool etatSouris);
    void coloriage(int coordX, int coordY);

    private:
    int m_coordXactif;
    int m_coordYactif;

    bool m_testSouris;

    QPixmap *chipsetBase;
    mapCell ***labelbis;

    QStatusBar *statusBar;

};

#endif
