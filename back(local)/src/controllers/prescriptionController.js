const pool = require("../config/db");



const getAllPrescriptions = async(req,res) =>
{
    try
    {
        const result =
            await pool.query(

                `
                SELECT
                    prescriptions.id,
                    prescriptions.patient_id,
                    prescriptions.disease_id,
                    prescriptions.created_by,
                    prescriptions.diagnosis,
                    prescriptions.created_at,

                    patients.full_name AS patient_name,

                    diseases.name AS disease_name,

                    'Doctor' AS doctor_name

                FROM prescriptions

                LEFT JOIN patients
                ON prescriptions.patient_id = patients.id

                LEFT JOIN diseases
                ON prescriptions.disease_id = diseases.id

                ORDER BY prescriptions.id ASC
                `
            );

        res.status(200).json({

            success:true,

            total:result.rows.length,

            data:result.rows
        });
    }

    catch(error)
    {
        console.error(
            "GET PRESCRIPTIONS ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};


const createPrescription = async(req,res) =>
{
    try
    {
        const
        {
            patient_id,
            disease_id,
            created_by,
            diagnosis
        } = req.body;

        const result =
            await pool.query(

                `
                INSERT INTO prescriptions
                (
                    patient_id,
                    disease_id,
                    created_by,
                    diagnosis
                )

                VALUES
                (
                    $1,$2,$3,$4
                )

                RETURNING *
                `,

                [
                    patient_id,
                    disease_id,
                    created_by,
                    diagnosis
                ]
            );

        res.status(201).json({

            success:true,

            message:"Prescription created",

            data:result.rows[0]
        });
    }

    catch(error)
    {
        console.error(
            "CREATE PRESCRIPTION ERROR:",
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
    getAllPrescriptions,
    createPrescription
};