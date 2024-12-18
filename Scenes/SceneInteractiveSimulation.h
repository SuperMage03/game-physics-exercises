#pragma once
#include "Scene.h"
#include <vector>

class SceneInteractiveSimulation : public Scene {
public:
    void init() override;
    void simulateStep() override;
    void onDraw(Renderer &renderer) override;
    void onGUI() override;

private:
    int m, n;             
    double dx, dy;         
    double nu;               
    double dt_sim;          
    bool isExplicitMethod; 

    std::vector<std::vector<double>> T_curr;  
    std::vector<std::vector<double>> T_next; 

    void initializeGrid();     
    void updateTemperature();
    void setTemperatureAtMouse(double temp);
};
