//
//  comparison.h
//  program 3
//
//  Created by Brandon Craven on 12/10/13.
//  Copyright (c) 2013 Brandon Craven. All rights reserved.
//

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
