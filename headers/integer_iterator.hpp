#ifndef INTEGER_ITERATOR_H
#define INTEGER_ITERATOR_H

#include "core_module.hpp"

#include <array>

/*
    this serves as an example for MVP, refer to main.cpp for what that actually is

    its a very simple module, and probably not useful for the final product
*/

class IntegerIterator : public CoreModule {
private:

public:
    IntegerIterator();

    CoreEvent hand_off_event_sync(CoreEvent) override;
    CoreEvent hand_off_event_sync(CoreDataEvent) override;

    void hand_off_event_async(CoreEvent) override;
    void hand_off_event_async(CoreDataEvent) override;
};

#endif