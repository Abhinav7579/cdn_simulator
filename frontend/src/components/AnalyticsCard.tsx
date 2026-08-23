interface AnalyticsCardProps {
    title: string;
    value: string | number;
    subtitle?: string;
}

function AnalyticsCard({
    title,
    value,
    subtitle
}: AnalyticsCardProps) {

    return (
        <div className="bg-white rounded-xl shadow-md p-6">
            <p className="text-gray-500 text-sm">
                {title}
            </p>

            <h2 className="text-3xl font-bold mt-2">
                {value}
            </h2>

            {subtitle && (
                <p className="text-gray-400 text-sm mt-1">
                    {subtitle}
                </p>
            )}
        </div>
    );
}

export default AnalyticsCard;