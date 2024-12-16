#pragma once

#include "Scene.h"
#include "FiniteDifferenceSolver.h"
#include <imgui.h>

class TestScene : public Scene {
    float f_delta = 0.01;
    bool f_pause = true;
    FiniteDifferenceSolver::FD_HPRDBC2D_Solver f_solver;
    GridFunction::ScalarGridFunction2D f_heatField;

public:
    TestScene()
    {}

    void init() override {
        f_solver = std::move(FiniteDifferenceSolver::FD_HPRDBC2D_Solver(
            HeatProblem::HeatProblemRectDBC2D(
                glm::dvec2(-2., -2.),
                glm::dvec2(4., 4.),
                1.,
                [](glm::dvec2 point) {
                    return (point.x + 2) * (point.x - 2) * (point.y + 2) * (point.y - 2) / 3.5;
                },
                [](double x) {
                    return 0.;
                },
                [](double x) {
                    return 0.;
                },
                [](double y) {
                    return 0.;
                },
                [](double y) {
                    return 0.;
                }
            )
        ));
        f_heatField = f_solver.getInitialState(15, 15);

        // f_solver = std::move(FiniteDifferenceSolver::FD_HPRDBC2D_Solver(
        //     HeatProblem::HeatProblemRectDBC2D(
        //         glm::dvec2(0., 0.),
        //         glm::dvec2(2., 4.),
        //         1.,
        //         [](glm::dvec2 point) {
        //             return 0.;
        //         },
        //         [](double x) {
        //             return 0.;
        //         },
        //         [](double x) {
        //             return 0.;
        //         },
        //         [](double y) {
        //             return 0.;
        //         },
        //         [](double y) {
        //             return 0.;
        //         }
        //     )
        // ));
        // f_heatField = f_solver.getInitialState(5, 8);

        // f_heatField.setValue(1, 1, 6);
        // f_heatField.setValue(1, 2, 5);
        // f_heatField.setValue(1, 3, 1);
        // f_heatField.setValue(1, 4, -1);
        // f_heatField.setValue(1, 5, -2);
        // f_heatField.setValue(1, 6, -1);
        // f_heatField.setValue(2, 1, 4);
        // f_heatField.setValue(2, 2, 3);
        // f_heatField.setValue(2, 3, 0);
        // f_heatField.setValue(2, 4, -1);
        // f_heatField.setValue(2, 5, -3);
        // f_heatField.setValue(2, 6, -1);
        // f_heatField.setValue(3, 1, 3);
        // f_heatField.setValue(3, 2, 2);
        // f_heatField.setValue(3, 3, -1);
        // f_heatField.setValue(3, 4, -2);
        // f_heatField.setValue(3, 5, -4);
        // f_heatField.setValue(3, 6, -2);
    }

    void onDraw(Renderer &renderer) override {
        f_heatField.onDraw(renderer);
    }

    void simulateStep() override {
        if (!f_pause) {
            // f_solver.propagateStateExplicitOn(f_heatField, f_delta);
            f_solver.propagateStateImplicitOn(f_heatField, f_delta);
        }
    }

    void onGUI() override {
        ImGui::SliderFloat("Delta", &this->f_delta, 0.f, 0.1);
        ImGui::Checkbox("Pause", &this->f_pause);
        if (ImGui::IsKeyPressed(ImGuiKey_Space)) {
            this->f_pause = !this->f_pause;
        }
    }
};