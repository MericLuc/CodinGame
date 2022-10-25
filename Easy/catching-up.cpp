#include <bits/stdc++.h>

namespace env {

using Dims = std::pair<size_t, size_t>;

/*****************************************************************************/
class ICell
{
public:
    enum State
    {
        EMPTY = 0,
        WALL = 1 << 1
    };

public:
    ICell(uint x, uint y) noexcept : _x{x}, _y{y} {}
    virtual ~ICell() noexcept = default;

    virtual void clean(void) noexcept {}

    auto x(void) const noexcept { return _x; }
    auto y(void) const noexcept { return _y; }

    bool hasState(int st) const noexcept { return _state & st; }
    int  getState(void) const noexcept { return _state; }

    [[maybe_unused]] bool setState(int st) noexcept {
        if ( st != _state ) { 
            _state = st; 
            return true;
        }
        return false;
    }
    [[maybe_unused]] bool addState(State st) noexcept {
        if (!(_state & st)) {
            _state |= st;
            return true;
        }
        return false;
    }
    [[maybe_unused]] bool remState(State st) noexcept{
        if (_state & st) {
            _state &= ~st;
            return true;
        }
        return false;
    }

protected:
    uint _x, _y;
    int  _state{ EMPTY };
};

/*****************************************************************************/
class AStarCell : public ICell
{
public:
    AStarCell(uint x, uint y, AStarCell* parent = nullptr): ICell(x, y), _parent{parent} {}
    virtual ~AStarCell() noexcept = default;

    void clean(void) noexcept override { 
        _G = _H = 0; 
        _parent = nullptr; 
    }

    uint getScore() const noexcept { return _G + _H; }

    uint       _G{ 0 }, _H{ 0 };
    AStarCell* _parent;
};

/*****************************************************************************/
template<typename T, typename = std::enable_if_t<std::is_base_of_v<ICell, T>>>
class Graph
{
public:
    Graph(size_t width = 10, size_t height = 10) noexcept
      : _width{ width }
      , _height{ height }
    {
        resize(width, height);
    }

    virtual ~Graph() noexcept = default;

    [[maybe_unused]] void clean(void) noexcept
    {
        std::for_each(std::begin(_data), std::end(_data), [](auto& c) { c.clean(); });;
    }

    virtual void resize(size_t width, size_t height) noexcept
    {
        _width = width;
        _height = height;

        _data.clear();
        _data.reserve(_width * _height);
        for (size_t i{ 0 }; i < _height; ++i)
            for (size_t j{ 0 }; j < _width; ++j)
                _data.push_back(T(j, i));
    }

    auto getWidth(void) const noexcept { return _width; }
    auto getHeight(void) const noexcept { return _height; }
    Dims getSize(void) const noexcept { return { _width, _height }; }

    T* cell(size_t i, size_t j) const noexcept
    {
        return (i < _width && j < _height) ? &_data.at(i + j * _width) : nullptr;
    }

    char cardinal(T* src, T* dst) const noexcept {
        if ( nullptr == src || nullptr == dst || dst == src ) return ' ';
        if ( src->x() == dst->x() )
            return src->y() < dst->y() ? 'R' : 'L';
        if ( src->y() == dst->y() )
            return src->x() < dst->x() ? 'D' : 'U';
        return ' ';
    }

protected:
    size_t                 _width, _height;
    mutable std::vector<T> _data;
};

}

namespace algo {

template<typename T>
using HeuristicFunction = std::function<uint(T*, T*)>;

using CellsList = std::list<env::ICell*>;
using CellsSet = std::set<env::ICell*>;

/*****************************************************************************/
class Heuristic
{
public:
    static uint manhattan(env::AStarCell* src, env::AStarCell* dst) noexcept {
        auto delta{ getDelta(src, dst) };
        return static_cast<uint>(10 * (delta.first + delta.second));
    }
    static uint euclidean(env::AStarCell* src, env::AStarCell* dst) noexcept {
        auto delta{ getDelta(src, dst) };
        return static_cast<uint>(10 * sqrt(pow(delta.first, 2) + pow(delta.second, 2)));
    }
    static uint octagonal(env::AStarCell* src, env::AStarCell* dst) noexcept {
        auto delta{ getDelta(src, dst) };
        return 10 * (delta.first + delta.second) + (-6) * std::min(delta.first, delta.second);
    }

private:
    static std::pair<int, int> getDelta(env::AStarCell* s, env::AStarCell* d) noexcept {
        return { abs(static_cast<int>(s->x()) - static_cast<int>(d->x())),
                abs(static_cast<int>(s->y()) - static_cast<int>(d->y())) };
    }
};

/*****************************************************************************/
template<typename T>
class Impl
{
public:
    Impl() noexcept: _heuristic{ std::bind(&Heuristic::euclidean, std::placeholders::_1, std::placeholders::_2) }
  , _dirs{ 4 }
  {}
    virtual ~Impl() noexcept = default;

    [[maybe_unused]] virtual T* run(env::Graph<T>* world, T* start, T* end) noexcept;
protected:
    virtual bool _eligible(T* cell) noexcept {
        return (nullptr == cell) ? false : !cell->hasState(env::ICell::WALL);
    }

private:
    env::Graph<T>* _world{ nullptr };

    HeuristicFunction<T> _heuristic;
    uint                 _dirs;

    static const std::vector<std::pair<int, int>> DIRS;
};


template<typename T>
const std::vector<std::pair<int, int>> Impl<T>::DIRS{ { 0, 1 },   { 1, 0 }, { 0, -1 }, { -1, 0 },
                                                      { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 } };

template < typename T>
T* Impl<T>::run(env::Graph<T>* world, T* start, T* end) noexcept {
        _world = world;
        if (nullptr == _world || nullptr == start || nullptr == end)
            return nullptr;

        env::AStarCell* cur{ nullptr };
        CellsList  open;
        CellsSet   closed;

        open.push_back(start);

        while (!std::empty(open)) {
            auto it{ std::max_element(std::begin(open), std::end(open), [](auto* a, auto* b) {
                return static_cast<env::AStarCell*>(a)->getScore() >= static_cast<env::AStarCell*>(b)->getScore();
            }) };
            cur = static_cast<env::AStarCell*>(*it);

            if (end == cur)
                break;

            closed.insert(cur);
            open.erase(it);

            for (uint i{ 0 }; i < _dirs; ++i) {
                auto neigh{ _world->cell(cur->x() + DIRS[i].first, cur->y() + DIRS[i].second) };
                if (!_eligible(neigh) || closed.count(neigh))
                    continue;

                uint totalCost{ cur->_G + ((i < 4) ? 10 : 14) };

                if (std::end(open) == std::find(std::begin(open), std::end(open), neigh)) {
                    neigh->_parent = cur;
                    neigh->_G = totalCost;
                    neigh->_H = _heuristic(neigh, end);
                    open.push_back(neigh);
                } else if (totalCost < neigh->_G) {
                    neigh->_parent = cur;
                    neigh->_G = totalCost;
                }
            }
        }

        if (cur != end)
            return nullptr;

        while (start != cur->_parent ) { cur = cur->_parent; }
        return cur;
    }
}

/*****************************************************************************/
int main()
{
    int k;
    std::cin >> k; std::cin.ignore();

    env::Graph<env::AStarCell> graph;
    algo::Impl<env::AStarCell> algo;
    env::AStarCell*            me{ nullptr }, *opp{ nullptr }; 

    for ( auto i{ 0 }; i < 10; ++i ) {
        std::string line;
        getline(std::cin, line);

        for ( auto j{ 0 }; j < 10; ++j ) {
            auto cell{ graph.cell(i, j) };
            switch ( line[j] ) {
                case '*': cell->setState(env::ICell::WALL); break;
                case 'P': me  = cell;                       break;
                case 'E': opp = cell;                       break;
                default:                                    break;
            }
        }
    }

    while (1) {
        int ene_y, ene_x;
        std::cin >> ene_y >> ene_x; std::cin.ignore();

        graph.clean();
        opp = graph.cell(ene_y, ene_x);

        if ( auto nxtCell{ algo.run(&graph, me, opp) }; nullptr != nxtCell ) {
            std::cout << graph.cardinal(me, nxtCell) << '\n';
            me = nxtCell;
        }
    }
}