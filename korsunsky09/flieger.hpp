#include <iostream>
#include <utility>

#ifndef FLIEGER_HPP
#define FLIGER_HPP

struct C_flieger {
    // first is x, second is y
    typedef std::pair<int, int> vec_t;

    // initializing constructor
    C_flieger(
        int t0, // starting time
        const vec_t& pos_0, // position at starting time
        const vec_t& velocity_, // initial velocity
        int altitude_ // initial altitude
    )
        :  tv(t0), last_pos(pos_0), velocity(velocity_), altitude(altitude_)
    {}

    // Zero constructor. Initialize everyithing to zero
    C_flieger()
        :tv(0), last_pos(0,0), velocity(0,0), altitude(0)
    {}

    // return position at time t
    vec_t Position(int t) const
    {
        // calculate new position
        return move(t-tv, last_pos, velocity);
    }

    void Steig(int dh) { altitude += dh; }

    void Speed(int vx, int vy, int t)
    {
        // move airplane to the new position
        last_pos = move(t-tv, last_pos, velocity);

        // set new time, set new velocity vector
        tv = t; velocity = std::make_pair(vx,vy);
    }

    void Zeigposition(int t)
    {
        vec_t pos = move(t-tv, last_pos, velocity);

        // print position:
        std::cout<<"Status des Flugzeuges zum Zeitpunkt "<<t<<": \n"
            "\tPosition: ("<<pos.first<<", "<<pos.second<<")\n"
            "\tHöhe: "<<altitude<<'\n'<<
            "\tGeschwindigkeit: ("<<velocity.first<<", "<<velocity.second<<")\n"
            <<std::endl;
    }
protected:
    // calculate new position based on old position, velocity and time elapsed
    static vec_t move(int dt, vec_t pos, vec_t vel)
    {
        return std::make_pair(pos.first+dt*vel.first, pos.second+dt*vel.second);
    }

    int tv; // time of the last change
    vec_t last_pos; // position at the last change
    vec_t velocity; // current velocity
    int altitude; // current altitude
};

// return wether the two positions are not further away than dist
inline bool dist_smaller(
    const C_flieger::vec_t& pos1,
    const C_flieger::vec_t& pos2, unsigned dist)
{
    return
        static_cast<unsigned>((pos1.first-pos1.first)*(pos1.first-pos1.first) +
        (pos1.first-pos1.second)*(pos1.first-pos1.second)) < dist;
}

inline
void Kollisionstest(const C_flieger& f1, const C_flieger& f2, int t0, int t1)
{
    for (int t = t0; t <= t1; ++t)
    {
        if( dist_smaller(f1.Position(t),f2.Position(t), 10u) )
            std::cout<<"WARNUNG: Entfernung zum Zeitpunkt t = "<<t<<" kleiner als 10 m!\n";
    }
}

#endif
