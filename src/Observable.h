#ifndef OBSERVABLE_H
#define OBSERVABLE_H

/**
 * \file Observable.h
 * \brief Définition de la classe Observable
 * \author J. Keenens
 * \version 0.1
 * \date 07/03/2016
 */

#include <memory>
#include <vector>
#include "Observer.h"

/**
 * \namespace Espace de nom pour les projets de J. Keenens
 */
namespace G36631 {

/**
 * \class Observable
 * \brief Représente "quelque chose" qui doit avertir des observateurs
 */
class Observable
{
public:
    /**
     * \brief Destructeur généré par le compilateur
     */
    virtual ~Observable() = default;

    /**
     * \brief Ajoute un observateur à avertir
     * \param observer : l'observateur
     */
    void addObserver(Observer* observer);
    /**
     * \brief Supprime un observateur
     * \param observer : l'observateur
     */
    void removeObserver(Observer *observer);

protected:
    std::vector<Observer*> m_observers; /**< La liste des observateurs à avertir */
};

}

#endif // OBSERVABLE_H
