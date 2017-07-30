#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QtGui>
#include <vector>
#include <string>
#include <unistd.h> //pour le usleep
#include <ctime>
#include <string>


#include "ville.h"
#include "chemin.h"
#include <fstream> // pour le fichier
#include "foncAux.h"
#include "algGen.h"
#include "crodpx.h"
#include "cropmx.h"

#include <QCheckBox>

namespace Ui {
class MainWindow;
}

/**
 * @brief C'est le destructeur de la classe
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * @brief Le constructeur de la classe
     *
     * @param parent Il recoit le valeur zero au début
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * @brief
     *
     */
    ~MainWindow();


    /**
     * @brief L'idee de ce methode est prendre les villes dans le fichier d'entree charge par "loadVilles" et les
     * mettres dans une structure de vecteur d'objets de Ville pour après produire les solutions.
     *
     * @param fichier
     * @return std::vector<Ville *> Il retourne le vecteur d'objets de type "Ville"
     */
    void lireFichier(QString fichier);

    /**
     * @brief Mettre à jour les "points" avec le meilleur chemin
     *
     * @param ch L'ensemble de solutions pour le problème
     * @param vil L'ensemble villes pour laquelles se passent les chemins
     * @param points C'est une structure de coordonnees du QT
     */
    void atualizaChemin (vector<string> ch, QPointF *points);

    /**
     * @brief C'est la fonction responsable pour les liens entre les signals et slots avec la finalite de faire
     * l'affichage du programme.
     *
     */
    void window();

    /**
     * @brief Ce methode fait le dessin des chemins pour l'affichage
     *
     * @param ch L'ensemble de solutions pour le probleme
     * @param vil L'ensemble villes pour laquelles se passent les chemins
     */
    void draw (vector<string> ch);

    void clearChemin(std::vector<Chemin*> &vche, int tam);

    void clearVilles();


public slots:
    /**
     * @brief Il fait le chargement du fichier choisi par l'utilisateur du programme pour les villes qui seront
     * parcourues pendant l'execution.
     *
     */
    void loadVilles();

    /**
     * @brief C'est la classe ou toutes les choses arrive, les objets sont crees et ou' on fait les liens entres
     * leurs fonctions principales pour resoudre le probleme du voyageur de commerce.
     *
     * @param i C'est le choix pour le croisement 'a etre utiliser dans l'execution du programme.
     */
    void TSP();

private:
    Ui::MainWindow *ui; /**< TODO */
    QPushButton *bLoad; /**< TODO */
    QPushButton *bTSP; /**< TODO */
    QHBoxLayout *mainLayout; /**< TODO */
    QVBoxLayout *layoutCkBox; /**< TODO */
    QVBoxLayout *layoutCkBox2; /**< TODO */
    QVBoxLayout *layoutPop; /**< TODO */

    QVBoxLayout *buttons; /**< TODO */
    QLabel label; /**< TODO */

    QRadioButton *alg1;
    QRadioButton *alg2;

    QRadioButton *mut1;
    QRadioButton *mut2;

    QLineEdit *myline;

    QWidget *widgetprincipal; /**< TODO */

    QPixmap pixmap; /**< TODO */


    std::vector < Ville * > vil; /**< TODO */

};

#endif // MAINWINDOW_H
