
#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "Events.h"
/**
 * Interface for the Observer
 */
class Observer {
    
public:
    
    virtual void update(Event event) = 0;
    
};


#endif //OBSERVER_HPP
