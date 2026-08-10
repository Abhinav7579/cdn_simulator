import axios from "axios";

import type { SimulationState } from "../types/simulation";

const API = "http://localhost:5000/api";

export const runSimulation = async (): Promise<SimulationState> => {

    const response = await axios.post<SimulationState>(
        `${API}/simulator`
    );

    return response.data;
};