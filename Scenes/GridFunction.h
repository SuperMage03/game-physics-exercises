#pragma once

#include "Grid.h"

namespace GridFunction {

    class IntegerGridScalarFunction2D {
    private:
        // Grid dimensions
        // Dimension wrt X
        unsigned f_n; 
        // Dimension wrt Y
        unsigned f_m;

        // Function values
        std::vector<std::vector<double>> f_values;

    public:

        #pragma region Constructors

        IntegerGridScalarFunction2D():
        f_n(0),
        f_m(0),
        f_values(0.)
        {}

        IntegerGridScalarFunction2D(const IntegerGridScalarFunction2D& other):
        f_n(other.f_n),
        f_m(other.f_m),
        f_values(other.f_values)
        {}

        IntegerGridScalarFunction2D(IntegerGridScalarFunction2D&& other):
        f_n(other.f_n),
        f_m(other.f_m),
        f_values(std::move(other.f_values))
        {}

        IntegerGridScalarFunction2D(
            unsigned n,
            unsigned m
        ):
        f_n(n),
        f_m(m)
        {
            resize();
        }

        IntegerGridScalarFunction2D(
            unsigned n,
            unsigned m,
            double value
        ):
        f_n(n),
        f_m(m)
        {
            f_values.resize(n);
            for (unsigned i = 0; i < n; i++) {
                f_values[i].resize(m);
                for (unsigned j = 0; j < m; j++) {
                    f_values[i][j] = value;
                }
            }
        }

        private:
        
        void resize() {
            f_values.resize(f_n);
            for (unsigned i = 0; i < f_n; i++) {
                f_values[i].resize(f_m);
            }
        }

        #pragma endregion

        #pragma region Getters and Setters

    public:

        unsigned getN() const {return f_n;}

        unsigned getM() const {return f_m;}

        double getValue(unsigned i, unsigned j) {
            // Check if invalid indices
            if (i >= f_n || j >= f_m) return 0.;
            return f_values[i][j];
        }

        bool setValue(unsigned i, unsigned j, double value) {
            // Check if invalid indices
            if (i >= f_n || j >= f_m) return false;

            f_values[i][j] = value;
            return true;
        }

        bool addToValue(unsigned i, unsigned j, double value) {
            if (i >= f_n || j >= f_m) return false;

            f_values[i][j] += value;
            return true;
        }

        void setAllValues(double value) {
            for (unsigned i = 0; i < f_n; i++) {
                for (unsigned j = 0; j < f_m; j++) {
                    f_values[i][j] = value;
                }
            }
        }

        void clear() {
            f_n = 0;
            f_m = 0;

            for (unsigned i = 0; i < f_n; i++) {
                f_values[i].clear();
            }
            f_values.clear();
        }

        void reallocate(unsigned n, unsigned m) {
            clear();
            f_n = n;
            f_m = m;
            resize();
        }

        #pragma endregion

        IntegerGridScalarFunction2D& operator=(const IntegerGridScalarFunction2D& other) {
            if (this == &other) return *this;
            clear();

            f_n = other.f_n;
            f_m = other.f_m;
            f_values = other.f_values;

            return *this;
        }

        IntegerGridScalarFunction2D& operator=(IntegerGridScalarFunction2D&& other) {
            if (this == &other) return *this;
            clear();

            f_n = other.f_n;
            f_m = other.f_m;
            f_values = std::move(other.f_values);

            return *this;
        }
    };

    class ScalarGridFunction2D {
    private:
        // Grid
        Grid::Grid2D f_grid;

        // Inreger grid function
        IntegerGridScalarFunction2D f_function;
    
    public:
        #pragma region Constructors

        ScalarGridFunction2D():
        f_grid(),
        f_function()
        {}

        ScalarGridFunction2D(
            unsigned n,
            unsigned m,
            const glm::dvec2& origin,
            const glm::dvec2& size
        ):
        f_grid(n, m, origin, size),
        f_function(n, m)
        {}

        ScalarGridFunction2D(
            unsigned n,
            unsigned m,
            glm::dvec2&& origin,
            glm::dvec2&& size
        ):
        f_grid(n, m, origin, size),
        f_function(n, m)
        {}

        ScalarGridFunction2D(
            unsigned n,
            unsigned m,
            const glm::dvec2& origin,
            const glm::dvec2& size,
            double value
        ):
        f_grid(n, m, origin, size),
        f_function(n, m, value)
        {}

        ScalarGridFunction2D(
            unsigned n,
            unsigned m,
            glm::dvec2&& origin,
            glm::dvec2&& size,
            double value
        ):
        f_grid(n, m, origin, size),
        f_function(n, m, value)
        {}

        #pragma endregion

        #pragma region Getters and Setters
        
        glm::dvec2 getPoint(unsigned i, unsigned j) const {
            return f_grid.getPoint(i, j);
        }

        unsigned getN() const {return f_function.getN();}

        unsigned getM() const {return f_function.getM();}

        Grid::Grid2D getGrid() const {return f_grid;}

        GridFunction::IntegerGridScalarFunction2D getIntegerGridScalarFunction() const {return f_function;}

        double getValue(unsigned i, unsigned j) {
            return f_function.getValue(i, j);
        }

        glm::dvec2 getSteps() const {return f_grid.getSteps();}

        double getStepX() const {return f_grid.getStepX();}
        
        double getStepY() const {return f_grid.getStepY();}

        void setOrigin(const glm::dvec2& origin) {
            f_grid.setOrigin(origin);
        }

        void setSize(const glm::dvec2& size) {
            f_grid.setSize(size);
        }

        bool setValue(unsigned i, unsigned j, double value) {
            return f_function.setValue(i, j, value);
        }

        bool addToValue(unsigned i, unsigned j, double value) {
            return f_function.addToValue(i, j, value);
        }

        void setAllValues(double value) {
            f_function.setAllValues(value);
        }

        void clear() {
            f_function.clear();
            f_grid.clear();
        }

        void reallocate(unsigned n, unsigned m) {
            f_function.reallocate(n, m);
            f_grid.setNM(n, m);
        }

        void reallocate(
            unsigned n, 
            unsigned m,
            const glm::dvec2& origin,
            const glm::dvec2& size
        ) {
            f_function.reallocate(n, m);
            f_grid.setOrigin(origin);
            f_grid.setSize(size);
            f_grid.setNM(n, m);
        }

        #pragma endregion

        glm::dvec3 getColorForValue(double value) {
            float base = 3.;
            if (value <= 0.) {
                double t = (value + base) / base;
                return (1. - t) * glm::dvec3(0., 0., 1.) + t * glm::dvec3(1., 0., 0.);
            } 
            else {
                double t = value / base;
                return (1. - t) * glm::dvec3(1., 0., 0.) + t * glm::dvec3(1., 0.8, 0.);
            }
        }

        void onDraw(Renderer &renderer, glm::dvec3 shift = glm::dvec3(0.), double scale = 1.) {
            f_grid.onDraw(renderer, shift, scale);
            for (unsigned i = 0; i < f_function.getN(); i++) {
                for (unsigned j = 0; j < f_function.getM(); j++) {
                    renderer.drawSphere(
                        shift + scale * (f_grid.getPoint3D(i, j) + glm::dvec3(0., 0., f_function.getValue(i, j))),
                        0.015,
                        glm::vec4(getColorForValue(f_function.getValue(i, j)), 1.)
                    );
                }
            }
            for (unsigned i = 0; i < f_function.getN() - 1; i++) {
                for (unsigned j = 0; j < f_function.getM() - 1; j++) {
                    renderer.drawLine(
                        shift + scale * (f_grid.getPoint3D(i, j) + glm::dvec3(0., 0., f_function.getValue(i, j))),
                        shift + scale * (f_grid.getPoint3D(i + 1, j) + glm::dvec3(0., 0., f_function.getValue(i + 1, j))),
                        getColorForValue(f_function.getValue(i, j)),
                        getColorForValue(f_function.getValue(i + 1, j))
                    );
                    renderer.drawLine(
                        shift + scale * (f_grid.getPoint3D(i, j) + glm::dvec3(0., 0., f_function.getValue(i, j))),
                        shift + scale * (f_grid.getPoint3D(i, j + 1) + glm::dvec3(0., 0., f_function.getValue(i, j + 1))),
                        getColorForValue(f_function.getValue(i, j)),
                        getColorForValue(f_function.getValue(i, j + 1))
                    );
                }
            }
            // Draw remaining lines
            for (unsigned i = 0; i < f_function.getN() - 1; i++) {
                unsigned j = f_function.getM() - 1;
                renderer.drawLine(
                    shift + scale * (f_grid.getPoint3D(i, j) + glm::dvec3(0., 0., f_function.getValue(i, j))),
                    shift + scale * (f_grid.getPoint3D(i + 1, j) + glm::dvec3(0., 0., f_function.getValue(i + 1, j))),
                    getColorForValue(f_function.getValue(i, j)),
                    getColorForValue(f_function.getValue(i + 1, j))
                );
            }

            for (unsigned j = 0; j < f_function.getM() - 1; j++) {
                unsigned i = f_function.getN() - 1;
                renderer.drawLine(
                    shift + scale * (f_grid.getPoint3D(i, j) + glm::dvec3(0., 0., f_function.getValue(i, j))),
                    shift + scale * (f_grid.getPoint3D(i, j + 1) + glm::dvec3(0., 0., f_function.getValue(i, j + 1))),
                    getColorForValue(f_function.getValue(i, j)),
                    getColorForValue(f_function.getValue(i, j + 1))
                );
            }
        }
    };

    class IntegerGridScalarFunction3D {
    private:
        // Grid dimensions
        // Dimension wrt X
        unsigned f_n; 
        // Dimension wrt Y
        unsigned f_m;
        // Dimension wrt Z
        unsigned f_p;

        // Function values
        std::vector<std::vector<std::vector<double>>> f_values;

    public:

        #pragma region Constructors

        IntegerGridScalarFunction3D():
        f_n(0),
        f_m(0),
        f_p(0),
        f_values(0.)
        {}

        IntegerGridScalarFunction3D(const IntegerGridScalarFunction3D& other):
        f_n(other.f_n),
        f_m(other.f_m),
        f_p(other.f_p),
        f_values(other.f_values)
        {}

        IntegerGridScalarFunction3D(IntegerGridScalarFunction3D&& other):
        f_n(other.f_n),
        f_m(other.f_m),
        f_p(other.f_p),
        f_values(std::move(other.f_values))
        {}

        IntegerGridScalarFunction3D(
            unsigned n,
            unsigned m,
            unsigned p
        ):
        f_n(n),
        f_m(m),
        f_p(p)
        {
            resize();
        }

        IntegerGridScalarFunction3D(
            unsigned n,
            unsigned m,
            unsigned p,
            double value
        ):
        f_n(n),
        f_m(m),
        f_p(p)
        {
            f_values.resize(n);
            for (unsigned i = 0; i < n; i++) {
                f_values[i].resize(m);
                for (unsigned j = 0; j < m; j++) {
                    f_values[i][j].resize(p);
                    for (unsigned k = 0; k < p; k++) {
                        f_values[i][j][k] = value;
                    }
                }
            }
        }

        private:
        
        void resize() {
            f_values.resize(f_n);
            for (unsigned i = 0; i < f_n; i++) {
                f_values[i].resize(f_m);
                for (unsigned j = 0; j < f_m; j++) {
                    f_values[i][j].resize(f_p);
                }
            }
        }

        #pragma endregion

        #pragma region Getters and Setters

    public:

        unsigned getN() const {return f_n;}

        unsigned getM() const {return f_m;}

        unsigned getP() const {return f_p;}

        double getValue(unsigned i, unsigned j, unsigned k) {
            // Check if invalid indices
            if (i >= f_n || j >= f_m || k >= f_p) return 0.;
            return f_values[i][j][k];
        }

        bool setValue(unsigned i, unsigned j, unsigned k, double value) {
            // Check if invalid indices
            if (i >= f_n || j >= f_m || k >= f_p) return false;

            f_values[i][j][k] = value;
            return true;
        }

        bool addToValue(unsigned i, unsigned j, unsigned k, double value) {
            // Check if invalid indices
            if (i >= f_n || j >= f_m || k >= f_p) return false;

            f_values[i][j][k] += value;
            return true;
        }

        void setAllValues(double value) {
            for (unsigned i = 0; i < f_n; i++) {
                for (unsigned j = 0; j < f_m; j++) {
                    for (unsigned k = 0; k < f_p; k++) {
                        f_values[i][j][k] = value;
                    }
                }
            }
        }

        void clear() {
            f_n = 0;
            f_m = 0;
            f_p = 0;

            for (unsigned i = 0; i < f_n; i++) {
                for (unsigned j = 0; j < f_m; j++) {
                    f_values[i][j].clear();
                }
                f_values[i].clear();
            }
            f_values.clear();
        }

        void reallocate(unsigned n, unsigned m, unsigned p) {
            clear();
            f_n = n;
            f_m = m;
            f_p = p;
            resize();
        }

        #pragma endregion

        IntegerGridScalarFunction3D& operator=(const IntegerGridScalarFunction3D& other) {
            if (this == &other) return *this;
            clear();

            f_n = other.f_n;
            f_m = other.f_m;
            f_p = other.f_p;
            f_values = other.f_values;

            return *this;
        }

        IntegerGridScalarFunction3D& operator=(IntegerGridScalarFunction3D&& other) {
            if (this == &other) return *this;
            clear();

            f_n = other.f_n;
            f_m = other.f_m;
            f_p = other.f_p;
            f_values = std::move(other.f_values);

            return *this;
        }
    };

    class ScalarGridFunction3D {
    private:
        // Grid
        Grid::Grid3D f_grid;

        // Inreger grid function
        IntegerGridScalarFunction3D f_function;
    
    public:
        #pragma region Constructors

        ScalarGridFunction3D():
        f_grid(),
        f_function()
        {}

        ScalarGridFunction3D(
            unsigned n,
            unsigned m,
            unsigned p,
            const glm::dvec3& origin,
            const glm::dvec3& size
        ):
        f_grid(n, m, p, origin, size),
        f_function(n, m, p)
        {}

        ScalarGridFunction3D(
            unsigned n,
            unsigned m,
            unsigned p,
            glm::dvec3&& origin,
            glm::dvec3&& size
        ):
        f_grid(n, m, p, origin, size),
        f_function(n, m, p)
        {}

        ScalarGridFunction3D(
            unsigned n,
            unsigned m,
            unsigned p,
            const glm::dvec3& origin,
            const glm::dvec3& size,
            double value
        ):
        f_grid(n, m, p, origin, size),
        f_function(n, m, p, value)
        {}

        ScalarGridFunction3D(
            unsigned n,
            unsigned m,
            unsigned p,
            glm::dvec3&& origin,
            glm::dvec3&& size,
            double value
        ):
        f_grid(n, m, p, origin, size),
        f_function(n, m, p, value)
        {}

        #pragma endregion

        #pragma region Getters and Setters
        
        glm::dvec3 getPoint(unsigned i, unsigned j, unsigned k) const {
            return f_grid.getPoint(i, j, k);
        }

        unsigned getN() const {return f_function.getN();}

        unsigned getM() const {return f_function.getM();}

        unsigned getP() const {return f_function.getP();}

        Grid::Grid3D getGrid() const {return f_grid;}

        GridFunction::IntegerGridScalarFunction3D getIntegerGridScalarFunction() const {return f_function;}

        double getValue(unsigned i, unsigned j, unsigned k) {
            return f_function.getValue(i, j, k);
        }

        glm::dvec3 getSteps() const {return f_grid.getSteps();}

        double getStepX() const {return f_grid.getStepX();}
        
        double getStepY() const {return f_grid.getStepY();}

        double getStepZ() const {return f_grid.getStepZ();}

        void setOrigin(const glm::dvec3& origin) {
            f_grid.setOrigin(origin);
        }

        void setSize(const glm::dvec3& size) {
            f_grid.setSize(size);
        }

        bool setValue(unsigned i, unsigned j, unsigned k, double value) {
            return f_function.setValue(i, j, k, value);
        }

        bool addToValue(unsigned i, unsigned j, unsigned k, double value) {
            return f_function.addToValue(i, j, k, value);
        }

        void setAllValues(double value) {
            f_function.setAllValues(value);
        }

        void clear() {
            f_function.clear();
            f_grid.clear();
        }

        void reallocate(unsigned n, unsigned m, unsigned p) {
            f_function.reallocate(n, m, p);
            f_grid.setNMP(n, m, p);
        }

        void reallocate(
            unsigned n, 
            unsigned m,
            unsigned p,
            const glm::dvec3& origin,
            const glm::dvec3& size
        ) {
            f_function.reallocate(n, m, p);
            f_grid.setOrigin(origin);
            f_grid.setSize(size);
            f_grid.setNMP(n, m, p);
        }

        #pragma endregion

        glm::dvec3 getColorForValue(double value) {
            float base = 3.;
            if (value <= 0.) {
                double t = (value + base) / base;
                return (1. - t) * glm::dvec3(0., 0., 1.) + t * glm::dvec3(1., 0., 0.);
            } 
            else {
                double t = value / base;
                return (1. - t) * glm::dvec3(1., 0., 0.) + t * glm::dvec3(1., 0.8, 0.);
            }
        }

        void onDraw(Renderer &renderer, glm::dvec3 shift = glm::dvec3(0.), double scale = 1.) {
            f_grid.onDraw(renderer, shift, scale);
            for (unsigned i = 0; i < f_function.getN(); i++) {
                for (unsigned j = 0; j < f_function.getM(); j++) {
                    for (unsigned k = 0; k < f_function.getP(); k++) {
                        renderer.drawCube(
                            shift + scale * f_grid.getPoint(i, j, k),
                            glm::quat(glm::vec3(0., 0., 0.)),
                            glm::vec3(f_grid.getStepX(), f_grid.getStepY(), f_grid.getStepZ()),
                            glm::vec4(getColorForValue(f_function.getValue(i, j, k)), 0.1)
                        );
                    }
                }
            }
        }
    };

}