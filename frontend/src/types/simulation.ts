export interface FileData {
    name: string;
    size: number;
    type: string;
}

export interface ServerData {
    name: string;
    status: boolean;
    cacheHits: number;
    cacheMisses: number;
    currentLoad: number;
}

export interface AnalyticsData {
    totalRequests: number;
    cacheHitRatio: number;
    averageResponseTime: number;
    mostRequestedFile: string;
}

export interface LogData {
    filename: string;
    server: string;
    cacheHit: boolean;
    originAccessed: boolean;
    responseTime: number;
    timestamp: string;
}

export interface SimulationState {
    origin: {
        files: FileData[];
    };

    loadBalancer: {
        strategy: string;
    };

    servers: ServerData[];

    analytics: AnalyticsData;

    logs: LogData[];
}