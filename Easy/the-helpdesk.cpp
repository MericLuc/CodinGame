#include <bits/stdc++.h>

struct Visitor { int helptime; Visitor(int helptime = 0): helptime{ helptime }{} };

struct Counter {
    typedef enum { AVAILABLE, BUSY, BREAK } STATUS;

    Counter(int id = 0, float efficiency = 0.f, float worktime = 0.f): 
        id{ id }, efficiency{ efficiency }, wTime{ worktime } {}
    STATUS advance(float time) {
        curTime += time;
        switch(status) {
            case AVAILABLE: return AVAILABLE;
            case BUSY: {
                consecwTime += time;
                wLoad = std::max(0.f, wLoad - time);
                if ( wLoad > 0.f ) return BUSY;
                if ( consecwTime >= wTime ) { 
                    status      = BREAK;  
                    consecwTime = 0;  
                    wLoad       = 10; 
                    lastBreakT  = curTime;
                    breaks++; 
                } 
                else { 
                    status = AVAILABLE;
                    wLoad =  0;
                }
            } break;
            case BREAK: {
                wLoad = std::max(0.f, wLoad - time);
                if ( wLoad > 0.f ) return BREAK;
                status = AVAILABLE, wLoad = 0.f;
            } break;
            
        }
        return AVAILABLE;
    }
    [[maybe_unused]] bool assign(Visitor vis) {
        if ( AVAILABLE != status )
            return false;
        
        status  = BUSY;
        wLoad   = vis.helptime / efficiency;
        clients++;

        return true;
    }
    float nextStep(void) const { return wLoad; }

    int    id{ 0 };
    STATUS status{ AVAILABLE };
    float  efficiency{ 1.f }, consecwTime{ 0.f }, wTime{ 0.f }, wLoad{ 0.f };
    float  curTime{ 0.f }, lastBreakT{ 0.f};
    int    clients{ 0 }, breaks{ 0 };
};

int main() {

    int   worktime, nc, nv, helptime;
    float efficiency;

    std::cin >> worktime >> nc; std::cin.ignore();

    std::deque<Visitor>  queue;
    std::vector<Counter> counters(nc);

    int id{ 0 };
    for (auto& ct : counters) {
        std::cin >> efficiency; std::cin.ignore();
        ct = Counter(++id, efficiency, worktime);
    }

    std::cin >> nv; std::cin.ignore();
    for (int i = 0; i < nv; i++) {
        std::cin >> helptime; std::cin.ignore();
        queue.push_back(helptime);
    }

    Counter* curCounter{ nullptr };
    const auto& getStep{ [&](){
        float stepT{ std::numeric_limits<float>::max() };
        for ( const auto& ct : counters ) {
            if ( auto nxt{ ct.nextStep() }; nxt < stepT ) {
                stepT = nxt;
            }
        }
        return stepT;
    } };

    const auto& advance{ [&](float stepT){
        curCounter = nullptr;
        for ( auto& ct : counters ) 
            if ( (Counter::STATUS::AVAILABLE == ct.advance(stepT)) && (nullptr == curCounter) )
                curCounter = &ct;
    } };

    const auto& processVisitor{ [&]() {
        if ( nullptr == curCounter ) return;
        if ( curCounter->assign(queue.front()) )
            queue.pop_front();
    } };

    float curTime{ 0.f }, stepTime{ 0.f };
    while ( !std::empty(queue) ) {
        stepTime = getStep();
        curTime += stepTime;
        advance(getStep());
        processVisitor();
    }

    for ( int i{ 0 }; i < std::size(counters); ++i )
        if ( counters[i].lastBreakT == curTime )
            counters[i].breaks--;

    for ( int i{ 0 }; i < std::size(counters); ++i )
        std::cout << ( (0 != i) ? " " : "" ) << counters[i].clients;
    std::cout << std::endl;

    for ( int i{ 0 }; i < std::size(counters); ++i )
        std::cout << ( (0 != i) ? " " : "" ) << counters[i].breaks;
    std::cout << std::endl;
}
