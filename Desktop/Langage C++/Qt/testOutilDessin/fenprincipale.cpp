#include "FenPrincipale.h"

FenPrincipale::FenPrincipale()
{

    setWindowTitle("Editeur de carte");
    setWindowIcon(QIcon("Icone.png"));


//création de la barre des menus
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");

        QAction *actionNouveau = new QAction("&Nouveau", this);
        menuFichier->addAction(actionNouveau);
        actionNouveau->setShortcut(QKeySequence("Ctrl+N"));
        actionNouveau->setIcon(QIcon("Nouveau.png"));
        //connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

        QAction *actionOuvrir = new QAction("&Ouvrir cartes", this);
        menuFichier->addAction(actionOuvrir);
        actionOuvrir->setShortcut(QKeySequence("Ctrl+O"));
        actionOuvrir->setIcon(QIcon("Ouvrir.png"));
        //connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

        QAction *actionEnregistrer = new QAction("&Enregistrer", this);
        menuFichier->addAction(actionEnregistrer);
        actionEnregistrer->setShortcut(QKeySequence("Ctrl+S"));
        actionEnregistrer->setIcon(QIcon("Enregistrer.png"));
        //connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

        menuFichier->addSeparator();

        QAction *actionImporterProjet = new QAction("Importer un &projet", this);
        menuFichier->addAction(actionImporterProjet);

        QAction *actionImporterCarte = new QAction("Importer une &carte", this);
        menuFichier->addAction(actionImporterCarte);

        menuFichier->addSeparator();

        //nettoyer le projet, carte sans parent, effacer perso test...

        QAction *actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
        actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
        actionQuitter->setIcon(QIcon("Quitter.png"));
        connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    QMenu *menuEdition = menuBar()->addMenu("&Edition");

        QAction *actionAnnuler = new QAction("&Annuler", this);
        menuEdition->addAction(actionAnnuler);
        actionAnnuler->setShortcut(QKeySequence("Ctrl+Z"));
        actionAnnuler->setIcon(QIcon("Annuler.png"));

        menuEdition->addSeparator();

        QAction *actionCopier = new QAction("&Copier", this);
        menuEdition->addAction(actionCopier);
        actionCopier->setShortcut(QKeySequence("Ctrl+C"));
        actionCopier->setIcon(QIcon("Copier.png"));

        QAction *actionColler = new QAction("Coll&er", this);
        menuEdition->addAction(actionColler);
        actionColler->setShortcut(QKeySequence("Ctrl+V"));
        actionColler->setIcon(QIcon("Coller.png"));


    QMenu *menuMAJ = menuBar()->addMenu("&Mise à jour d'un projet");

    QMenu *menuAide = menuBar()->addMenu("&Aide");


//création de la barre d'outils
    QToolBar *toolBarFichier = addToolBar("Fichier");

    toolBarFichier->addAction(actionNouveau);
    toolBarFichier->addAction(actionOuvrir);
    toolBarFichier->addAction(actionEnregistrer);

    toolBarFichier->addSeparator();

    toolBarFichier->addAction(actionQuitter);

    toolBarFichier->addSeparator();

    toolBarFichier->addAction(actionAnnuler);

    toolBarFichier->addSeparator();

    toolBarFichier->addAction(actionColler);
    toolBarFichier->addAction(actionCopier);

    toolBarFichier->addSeparator();

    QSlider *zoom = new QSlider(Qt::Horizontal, this);
    toolBarFichier->addWidget(zoom);


//création de la zone centrale qui peut afficher une seule fenêtre

    QWidget *zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);

    QTabWidget *onglets = new QTabWidget(zoneCentrale);

    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(onglets);
    zoneCentrale->setLayout(layoutPrincipal);

    QWidget *general = new QWidget;
    QWidget *chipset = new QWidget;
    QWidget *monstre = new QWidget;
    QWidget *zoneDeMonstre = new QWidget;

    onglets->addTab(general, "Général");
    onglets->addTab(chipset, "Chipset");
    onglets->addTab(monstre, "Monstre");
    onglets->addTab(zoneDeMonstre, "Zone de monstre");

/* --------------- affichage dans l'onglet general -------------------*/

    //mon image de base

    chipsetBase = new QPixmap("LhynnBis.png");

    //layout pour diviser écran en deux
    QHBoxLayout *horizontal = new QHBoxLayout(general);

/* --------------------- partie chipset --------------------------*/

    //layout pour avoir une grille chipset
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setSpacing(0);

    // taille du chipset
    int tailleX = chipsetBase->width()/16;
    int tailleY = chipsetBase->height()/16;

    //definition du tableau de label
    chipsetCell ***label;
    label = new chipsetCell**[tailleX];
    for(int i=0;i<tailleX;i++)
    {
        label[i]=new chipsetCell*[tailleY];
    }
    for(int i=0;i<tailleX;i++)
    {
        for(int j=0;j<tailleY;j++)
        {
            label[i][j]=new chipsetCell;
            connect(label[i][j], SIGNAL(envoiCoord(int, int)), this, SLOT(receptionCoord(int, int)));
            label[i][j]->setText("");
            label[i][j]->setPixmap(chipsetBase->copy(16*i,16*j,16,16));
            label[i][j]->setFrameStyle(QFrame::Box);
            label[i][j]->setLineWidth(1);
            label[i][j]->setCoordX(i);
            label[i][j]->setCoordY(j);
            gridLayout->addWidget(label[i][j],j,i);
        }
    }

    //dans un scrollarea on ne peut mettre qu'un widget et pas un layout, on créé donc un widget inutile
    QWidget *widgetBidon = new QWidget;
    widgetBidon->setLayout(gridLayout);

    //création de la QScrollArea
    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Light);
    scrollArea->setWidget(widgetBidon);

    //ajout de la scrollArea dans la partie gauche
    horizontal->addWidget(scrollArea);

/* --------------------- partie map --------------------------*/

    //layout pour avoir une grille map
    QGridLayout *gridLayoutbis = new QGridLayout;
    gridLayoutbis->setSpacing(0);


    //definition du tableau de label
    //mapCell ***labelbis;
    labelbis = new mapCell**[tailleX];
    for(int i=0;i<tailleX;i++)
    {
        labelbis[i]=new mapCell*[tailleY];
    }
    for(int i=0;i<tailleX;i++)
    {
        for(int j=0;j<tailleY;j++)
        {
            labelbis[i][j]=new mapCell;
            //labelbis[i][j]->setMouseTracking(true);
            connect(labelbis[i][j], SIGNAL(envoiCoord(int, int)), this, SLOT(coloriage(int,int)));
            connect(labelbis[i][j], SIGNAL(envoiEtatSouris(bool)), this, SLOT(receptionEtatSouris(bool)));
            labelbis[i][j]->setText("");
            labelbis[i][j]->setPixmap(chipsetBase->copy(0,0,16,16));
            labelbis[i][j]->setFrameStyle(QFrame::Box);
            labelbis[i][j]->setLineWidth(1);
            labelbis[i][j]->setCoordX(i);
            labelbis[i][j]->setCoordY(j);
            gridLayoutbis->addWidget(labelbis[i][j],j,i);
        }
    }

    //dans un scrollarea on ne peut mettre qu'un widget et pas un layout, on créé donc un widget inutile
    QWidget *widgetBidonbis = new QWidget;
    widgetBidonbis->setLayout(gridLayoutbis);

    //création de la QScrollArea
    QScrollArea *scrollAreabis = new QScrollArea;
    scrollAreabis->setBackgroundRole(QPalette::Light);
    scrollAreabis->setWidget(widgetBidonbis);

    //ajout de la scrollArea dans la partie gauche
    horizontal->addWidget(scrollAreabis);


//bar de status
    statusBar = new QStatusBar;
    layoutPrincipal->addWidget(statusBar);
}


void FenPrincipale::receptionCoord(int coordX, int coordY)
{
    m_coordXactif = coordX;
    m_coordYactif = coordY;

    statusBar->showMessage(tr("Cellule chipset active : X=") + QString::number(m_coordXactif) + " Y= " + QString::number(m_coordYactif));
}

void FenPrincipale::coloriage(int coordX, int coordY)
{
    qDebug("coloriage");
    qDebug()<<m_testSouris << coordX << coordY;

    if (m_testSouris == true)
    {
        labelbis[coordX][coordY]->setPixmap(chipsetBase->copy(16*m_coordXactif,16*m_coordYactif,16,16));
    }
}

void FenPrincipale::receptionEtatSouris(bool etatSouris)
{
        m_testSouris = etatSouris;
}
