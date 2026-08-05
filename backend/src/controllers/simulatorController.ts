import type { Request, Response } from "express";

import { runSimulator } from "../services/simulatorService.js";

export const runSimulation = (
    req: Request,
    res: Response
) => {

    const result = runSimulator();

    res.json(result);

};