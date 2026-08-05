import express from "express";
import { runSimulation } from "../controllers/simulatorController.js";

const router = express.Router();

router.post("/", runSimulation);

export default router;