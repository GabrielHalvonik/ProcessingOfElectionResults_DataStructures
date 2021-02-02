#include "Sort.h"

Structures::SortNotifier::SortNotifier(int notificationPeriod): notificationPeriod_(notificationPeriod), currentNotification_(0) {
}

void Structures::SortNotifier::notify() {
        currentNotification_++;
        if (currentNotification_ == notificationPeriod_) {
                doNotify();
                currentNotification_ = 0;
        }
}
