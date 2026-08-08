import type { Request, Response } from "express";
import { runSimulator } from "../services/simulatorService.js";

export const runSimulation = async (
    req: Request,
    res: Response
) => {
    try {
        const data = await runSimulator();
        res.json(data);
    } catch (err) {
        console.error(err);

        res.status(500).json({
            error: err
        });
    }
};