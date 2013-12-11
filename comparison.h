/*
 Learned out to do this bit of code with help from this website:
 
 http://www.cplusplus.com/reference/queue/priority_queue/priority_queue/
 */

#ifndef __program_3__comparison__
#define __program_3__comparison__

#include "node.h"

class comparison
{
    bool reverse;
public:
    
    comparison(const bool& revparam = false)
    {
        reverse = revparam;
    }
    
    bool operator() (const node* lhs, const node* rhs) const
    {
        if (reverse)
            return lhs->getDistance() > rhs->getDistance();
        
        return lhs->getDistance() < rhs->getDistance();
    }
    
};


#endif /* defined(__program_3__comparison__) */
