import { runSimulator } from "../services/simulatorService.js";
export const runSimulation = async (req, res) => {
    try {
        const data = await runSimulator();
        res.json(data);
    }
    catch (err) {
        console.error(err);
        res.status(500).json({
            error: err
        });
    }
};
//# sourceMappingURL=simulatorController.js.map