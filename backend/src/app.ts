import express from "express";
import cors from "cors";

import simulatorRoutes from "./routes/simulatorRoutes.js";

const app = express();

app.use(cors());

app.use(express.json());

app.use("/api/simulator", simulatorRoutes);

export default app;