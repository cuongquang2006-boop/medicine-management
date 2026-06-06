const pool = require("../config/db");



const getDashboardStats =
    async(req,res) =>
{
    try
    {
        const patientResult =
            await pool.query(

                `
                SELECT COUNT(*) AS total
                FROM patients
                `
            );

        const medicineResult =
            await pool.query(

                `
                SELECT COUNT(*) AS total
                FROM medicines
                `
            );

        const clinicResult =
            await pool.query(

                `
                SELECT COUNT(*) AS total
                FROM clinics
                `
            );

        const prescriptionResult =
            await pool.query(

                `
                SELECT COUNT(*) AS total
                FROM prescriptions
                `
            );

        res.status(200).json({

            success:true,

            data:
            {
                patients:
                    patientResult.rows[0].total,

                medicines:
                    medicineResult.rows[0].total,

                clinics:
                    clinicResult.rows[0].total,

                prescriptions:
                    prescriptionResult.rows[0].total
            }
        });
    }

    catch(error)
    {
        console.error(
            "DASHBOARD STATS ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};

const getRecentPrescriptions =
    async(req,res) =>
{
    try
    {
        const result =
            await pool.query(

                `
                SELECT
                    patients.full_name AS patient,
                    diseases.name AS disease,

                    COUNT(
                        prescription_items.id
                    ) AS medicines,

                    prescriptions.created_at

                FROM prescriptions

                LEFT JOIN patients
                ON prescriptions.patient_id
                    = patients.id

                LEFT JOIN diseases
                ON prescriptions.disease_id
                    = diseases.id

                LEFT JOIN prescription_items
                ON prescriptions.id
                    = prescription_items.prescription_id

                GROUP BY
                    prescriptions.id,
                    patients.full_name,
                    diseases.name,
                    prescriptions.created_at

                ORDER BY
                    prescriptions.created_at DESC

                LIMIT 5
                `
            );

        res.status(200).json({

            success:true,

            data:result.rows
        });
    }

    catch(error)
    {
        console.error(
            "RECENT PRESCRIPTIONS ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};

const getLowStockMedicines =
    async(req,res) =>
{
    try
    {
        const result =
            await pool.query(

                `
                SELECT
                    name,
                    stock

                FROM medicines

                WHERE stock <= 5

                ORDER BY stock ASC

                LIMIT 5
                `
            );

        res.status(200).json({

            success:true,

            data:result.rows
        });
    }

    catch(error)
    {
        console.error(
            "LOW STOCK ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};


module.exports =
{
    getDashboardStats,
    getRecentPrescriptions,
    getLowStockMedicines
};