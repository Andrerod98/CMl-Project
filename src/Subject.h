#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include "Observer.h"
#include "Events.h"
/**
 * Interface for the Subject
 */
class Subject {
    
public:
    
    /**
     * Register an observer
     * @param observer the observer object to be registered
     */
    virtual void registerObserver(Observer *observer) = 0;
    
    /**
     * Unregister an observer
     * @param observer the observer object to be unregistered
     */
    virtual void removeObserver(Observer *observer) = 0;
    
    /**
     * Notify all the registered observers when a change happens
     */
    virtual void notifyObservers(Event event) = 0;
    
};


#endif //SUBJECT_HPP
