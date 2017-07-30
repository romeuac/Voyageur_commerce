#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::window()
{
    widgetprincipal = new QWidget();
    bLoad = new QPushButton("Load");
    bTSP = new QPushButton("Trouver Chemin");

    alg1 = new QRadioButton(tr("PMX"));
    alg2 = new QRadioButton(tr("DPX"));

    mut1 = new QRadioButton(tr("Standard"));
    mut2 = new QRadioButton(tr("Optimale"));

    myline = new QLineEdit;

    connect(bLoad, SIGNAL( clicked() ), this, SLOT( loadVilles() ) );
    connect(bTSP, SIGNAL( clicked() ), this, SLOT( TSP() ) );

    mainLayout = new QHBoxLayout();

    buttons = new QVBoxLayout();        //layout para os botoes
    buttons->addWidget(bLoad);
    buttons->addWidget(bTSP);
    mainLayout->addLayout(buttons);

    QGroupBox *groupBox1 = new QGroupBox(tr("Reprodution"));
    layoutCkBox = new QVBoxLayout();    //layout pour le checkbox
    layoutCkBox->addWidget(alg1);       //chacune des options de checkbox
    layoutCkBox->addWidget(alg2);
    alg1->setChecked(true);
    groupBox1->setLayout(layoutCkBox);
//    mainLayout->addLayout(layoutCkBox);  //adiciona o Layout do checkbox
    mainLayout->addWidget(groupBox1);

    QGroupBox *groupBox = new QGroupBox(tr("Mutation"));
    layoutCkBox2 = new QVBoxLayout();    //layout pour le mutation
    layoutCkBox2->addWidget(mut1);       //chacune des options de mutation
    layoutCkBox2->addWidget(mut2);
    mut1->setChecked(true);
    groupBox->setLayout(layoutCkBox2);
    //mainLayout->addLayout(layoutCkBox2);  //adiciona o Layout do mutation
    mainLayout->addWidget(groupBox);

    QGroupBox *BoxReprod = new QGroupBox(tr("Taille Population"));
    layoutPop = new QVBoxLayout();
    layoutPop->addWidget(myline);
    BoxReprod->setLayout(layoutPop);
    mainLayout->addWidget(BoxReprod);

    if (!pixmap.load( "./intro.jpg" )) {        //imagem inicial
       qWarning("Failed to load intro.png");
    }
    label.setPixmap(pixmap);

    mainLayout->addWidget(&label);

    widgetprincipal->setLayout(mainLayout);
    this->setCentralWidget(widgetprincipal);
}

//procura no vil o x e y de cada vila na ordem dada por ch. Depois altera o x e y de cada ponto no points
void MainWindow::atualizaChemin (vector<string> ch, QPointF * points)
{
    unsigned int i,j;

    for (i = 0 ; i < (ch).size() ; i++){
        j=0;

        while ( ch[i].c_str() != vil[j]->getID() ){
            j++;
        }
        points[i].setX(vil[j]->Ville::getX());
        points[i].setY(vil[j]->Ville::getY());
    }
}

void MainWindow::draw (vector<string> ch){

    QPointF points[vil.size()];

    QPainter painter;

    atualizaChemin(ch,points);

    if (vil[0]->getID().compare("TRELON") == 0){
        if (!pixmap.load( "./france.png" )) {
        qWarning("Failed to load ./target.png");
        }
    }else{
        if (!pixmap.load( "./branco.png" )) {
        qWarning("Failed to load ./target.png");
        }
        normaliza(points, vil.size());
    }

    painter.begin(&pixmap);
    QPen pen(Qt::blue,3);
    painter.setPen(pen);
    painter.drawPoints(points,vil.size());

    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawPolygon(points,vil.size());
    painter.end();

    label.setPixmap(pixmap);

    clearVilles();
}

void MainWindow::lireFichier (QString fichier)
{
    std::string ville;
    std::ifstream monFichier;

    QByteArray ba = fichier.toLatin1();
    char *c_str2 = ba.data();

    monFichier.open(c_str2);

    float a, b;			//coordenadas vilas

    if (monFichier.is_open ())
    {
        while (monFichier >> ville >> a >> b){
            vil.push_back (new Ville (ville, a, b));
        }
    }
    else{
        std::cout << "Unable to open file\n";
        exit(1);
    }
    monFichier.close();
}

void MainWindow::loadVilles(){
    QString arq = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Files (*.*)"));

    //On crée l'objet des villes
    lireFichier (arq);
}

void MainWindow::TSP(){
    std::vector < Chemin * > ch;
    algGen resoudre;
    croPMX pmx;
    croDPX dpx;
    float probDPX, probPMX;                     //Pour calculer la probabilité pour la multation
    QMessageBox msgCout;
    int pop;

    QString nPop;

    nPop.append(myline->text());

    char *taillePop = nPop.toLatin1().data();
    pop = atoi(taillePop);

    if (pop <= 1) pop = 30;   //pop stantard

    if (vil.size() == 0) lireFichier("villes.txt");

    //On initialise le variable de temps pour être calculé après dans la fonction "Temps" de foncAux
    time_t tstart = time(0);

    //On crée la matrice de couts
    resoudre.creerMat(vil);

    //On initialise le vecteur de chemins avec des valeurs aleatoires, avec 3 fois la grandeurs de la taille normal pour être dilinuer aprés dans la même fonction suivante
    resoudre.IniVecChemin(ch,3*pop);
    resoudre.IniModifChemin(ch,pop);

    pmx.setMat(resoudre.getMat());
    pmx.setVectcor(resoudre.getVectcor());
    dpx.setMat(resoudre.getMat());
    dpx.setVectcor(resoudre.getVectcor());
    //double start = omp_get_wtime();

    while( resoudre.Terminaison(ch, Temps(tstart), "160", "1400") != 1 )
    {
        //On augment le compteur des iteration de chaque chemin
        for (std::vector<Chemin*>::iterator it = (ch).begin(); it != (ch).end(); ++it) (*it)->AugCompt();

        //Il fait un calcule pour savoir si les croisement commence �  être pas eff-starticient...
        probDPX = (float)( (ch[(ch.size()*0.5)/1]->getCout() - ch[0]->getCout()) / (ch[ch.size() - 1]->getCout()) );
        probPMX = (float)( (ch[ch.size() - 1]->getCout() - ch[0]->getCout()) / (ch[ch.size() - 1]->getCout()) );

        //Il fait le croisement
        if (alg1->isChecked()){                                              //choix du algo de croisement
            if (mut1->isChecked()) pmx.CroisementPMX(ch, probPMX, "2");      //choix du algo de mutation
            else{
                if (mut2->isChecked()) pmx.CroisementPMX(ch, probPMX, "4");
                else {
                    std::cout << "Error dans la mutation" << std::endl;
                    exit (EXIT_FAILURE);
                }
            }
        }
        else{
            if(alg2->isChecked()){
                if (mut1->isChecked()) dpx.CroisementDPX(ch,probDPX,"2");      //choix du algo de mutation
                else{
                    if (mut2->isChecked()) pmx.CroisementPMX(ch, probPMX, "4");
                    else {
                        std::cout << "Error dans la mutation" << std::endl;
                        exit (EXIT_FAILURE);
                    }
                }
            }
            else {
                std::cout << "Erreur: choisir l'algorithme de reproduction" << std::endl;
                exit (EXIT_FAILURE);
            }
        }
    }
    //std::cout << (omp_get_wtime() - start) << " " << ch[0]->getCout() << std::endl;
    draw(ch[0]->getStr());


    char cout [10];
    sprintf(cout, "%.2f", ch[0]->getCout());

    clearChemin(ch,pop);            // deallocation de memoire
    resoudre.desaloca();
    vil.clear();

    msgCout.setText("Cout du meilleur chemin");     //boite du popup
    msgCout.setInformativeText(cout);
    msgCout.exec();
}

void MainWindow::clearVilles()
{
    unsigned i;

    for (i=0 ; i < vil.size() ; i++)
    {
        delete vil[i];
    }
}

void MainWindow::clearChemin(std::vector<Chemin*> &vche, int tam)
{
    std::cout << tam << std::endl;
    for(int i=0 ; i<tam ; i++) delete vche[i];
}
