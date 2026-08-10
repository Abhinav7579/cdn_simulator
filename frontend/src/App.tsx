import { useState } from "react";

import { runSimulation } from "./services/api";

import type { SimulationState } from "./types/simulation";

function App() {

    const [data, setData] = useState<SimulationState | null>(null);

    const handleRun = async () => {

        try {

            const result = await runSimulation();

            setData(result);

        } catch (error) {

            console.error(error);

        }
    };

    return (
        <div>

            <h1>CDN Simulator</h1>

            <button onClick={handleRun}>
                Run Simulation
            </button>

            {data && (
                <pre>
                    {JSON.stringify(data, null, 2)}
                </pre>
            )}

        </div>
    );
}

export default App;