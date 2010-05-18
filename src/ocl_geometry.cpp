/*  $Id$
 * 
 *  Copyright 2010 Anders Wallin (anders.e.e.wallin "at" gmail.com)
 *  
 *  This file is part of OpenCAMlib.
 *
 *  OpenCAMlib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  OpenCAMlib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with OpenCAMlib.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <boost/python.hpp>

#include "point.h"
#include "triangle.h"
#include "stlsurf.h"
#include "oellipse.h"
#include "cutter.h"

/*
 *  Python wrapping
 */

using namespace ocl;

namespace bp = boost::python;


void export_geometry() {
    bp::class_<Point>("Point") 
        .def(bp::init<double, double, double>())
        .def(bp::init<Point>())
        .def(bp::other<double>() * bp::self)
        .def(bp::self * bp::other<double>())
        .def(bp::self -= bp::other<Point>())
        .def(bp::self - bp::other<Point>())
        .def(bp::self += bp::other<Point>())
        .def(bp::self + bp::other<Point>())
        .def("norm", &Point::norm)
        .def("normalize", &Point::normalize)
        .def("dot", &Point::dot)
        .def("cross", &Point::cross)
        .def("isRight", &Point::isRight)
        .def("isInside", &Point::isInside)
        .def("isInsidePoints", &Point::isInside)
        .def("xyDistance", &Point::xyDistance)
        .def("__str__", &Point::str)
        .def_readwrite("x", &Point::x)
        .def_readwrite("y", &Point::y)
        .def_readwrite("z", &Point::z)
        .def_readonly("id", &Point::id)
    ;   
    bp::class_<CCPoint>("CCPoint") 
        .def(bp::init<CCPoint>())
        .def("__str__", &CCPoint::str)
        .def_readwrite("type", &CCPoint::type)
        .def_readwrite("x", &CCPoint::x)
        .def_readwrite("y", &CCPoint::y)
        .def_readwrite("z", &CCPoint::z)
    ;
    bp::enum_<CCType>("CCType")
        .value("NONE", NONE)
        .value("VERTEX",VERTEX)
        .value("EDGE",EDGE)
        .value("EDGE_HORIZ_CYL",EDGE_HORIZ_CYL)
        .value("EDGE_HORIZ_TOR",EDGE_HORIZ_TOR)
        .value("EDGE_POS",EDGE_POS)
        .value("EDGE_NEG",EDGE_NEG)
        .value("FACET", FACET)
        .value("FACET_TIP", FACET_TIP)
        .value("FACET_CYL", FACET_CYL)
        .value("ERROR", ERROR)
    ;
    bp::class_<Triangle>("Triangle")
        .def(bp::init<Point,Point,Point>())
        .def("getPoints", &Triangle::getPoints)
        .def("__str__", &Triangle::str) 
        .def_readonly("p", &Triangle::p)
        //.def_readonly("n", &Triangle::n)
        .def_readonly("id", &Triangle::id)
    ;
    bp::class_<STLSurf>("STLSurf")
        .def(bp::init<const std::wstring&>())
        .def("addTriangle", &STLSurf::addTriangle)
        .def("__str__", &STLSurf::str)
        .def("size", &STLSurf::size)
        .def_readonly("tris", &STLSurf::tris)
        .def_readonly("id", &STLSurf::id)
        .def("build_kdtree", &STLSurf::build_kdtree)
        .def("get_kd_triangles", &STLSurf::get_kd_triangles)
        .def("jump_kd_up", &STLSurf::jump_kd_up)
        .def("jump_kd_hi", &STLSurf::jump_kd_hi)
        .def("jump_kd_lo", &STLSurf::jump_kd_lo)
        .def("jump_kd_reset", &STLSurf::jump_kd_reset)
        .def("get_kd_level", &STLSurf::get_kd_level)
        .def("get_kd_cut", &STLSurf::get_kd_cut)
        .def("getTrianglesUnderCutter", &STLSurf::getTrianglesUnderCutter)
    ;
    bp::class_<Epos>("Epos")
        .def("setS", &Epos::setS)
        .def("setT", &Epos::setT)
        .def("stepTangent", &Epos::stepTangent)
        .def_readwrite("s", &Epos::s)
        .def_readwrite("t", &Epos::t)
        .def("__str__", &Epos::str)
    ;
    bp::class_<Ellipse>("Ellipse")
        .def(bp::init<Point&, double, double, double>())
        .def("ePoint", &Ellipse::ePoint)
        .def("oePoint", &Ellipse::oePoint)
        .def("normal", &Ellipse::normal)
        .def("tangent", &Ellipse::tangent)
        .def("error", &Ellipse::error)
        .def("solver", &Ellipse::solver)
        .def_readonly("epos1", &Ellipse::epos1)
        .def_readonly("epos2", &Ellipse::epos2)
        .def_readonly("center", &Ellipse::center)
    ;

}
