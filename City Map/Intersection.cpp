//
//  Intersection.cpp
//  City Map
//
//  Created by Kaloyan Dimov on 12.05.22.
//

#include "Intersection.hpp"

Intersection::Intersection(const std::string& _name):
    name{_name} {}

const std::string& Intersection::get_name() const {
    return name;
}

const std::vector<Street>& Intersection::get_streets() const {
    return streets;
}

unsigned Intersection::get_indegree() const {
    return indegree;
}

unsigned Intersection::get_outdegree() const {
    return outdegree;
}

void Intersection::add_street(const Street& street) {
    streets.push_back(street);
    street.head->outdegree++;
    street.tail->indegree++;
}

void Intersection::add_street(Intersection* head, unsigned distance, Intersection* tail) {
    add_street({head, distance, tail});
}
