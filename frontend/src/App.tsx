import { useState } from "react";

import { runSimulation } from "./services/api";

import type { SimulationState } from "./types/simulation";

import AnalyticsCard from "./components/AnalyticsCard";

function App() {

    const [data, setData] = useState<SimulationState | null>(null);

    const [loading, setLoading] = useState(false);

    const handleRunSimulation = async () => {

        try {

            setLoading(true);

            const result = await runSimulation();

            setData(result);

        } catch (error) {

            console.error("Simulation failed:", error);

        } finally {

            setLoading(false);

        }
    };

    return (
        <div className="min-h-screen bg-gray-100 p-8">

            <div className="max-w-7xl mx-auto">

                <div className="flex justify-between items-center mb-8">

                    <div>
                        <h1 className="text-3xl font-bold">
                            CDN Simulator
                        </h1>

                        <p className="text-gray-500 mt-1">
                            Distributed Content Delivery Network
                        </p>
                    </div>

                    <button
                        onClick={handleRunSimulation}
                        disabled={loading}
                        className="bg-black text-white px-5 py-3 rounded-lg"
                    >
                        {loading
                            ? "Running..."
                            : "Run Simulation"
                        }
                    </button>

                </div>


                {data && (

                    <div>

                        {/* Analytics */}

                        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-5">

                            <AnalyticsCard
                                title="Total Requests"
                                value={data.analytics.totalRequests}
                            />

                            <AnalyticsCard
                                title="Cache Hit Ratio"
                                value={`${data.analytics.cacheHitRatio.toFixed(2)}%`}
                            />

                            <AnalyticsCard
                                title="Avg Response Time"
                                value={`${data.analytics.averageResponseTime.toFixed(2)} ms`}
                            />

                            <AnalyticsCard
                                title="Most Requested File"
                                value={data.analytics.mostRequestedFile}
                            />

                        </div>

                    </div>

                )}

            </div>

        </div>
    );
}

export default App;