const pool = require("../config/db");


const getAllDiseases = async(req,res) =>
{
    try
    {
        const result =
            await pool.query(

                `
                SELECT
                    diseases.id,
                    diseases.name,
                    clinics.name AS clinic_name,
                    diseases.description,
                    diseases.created_at,
                    diseases.symptoms

                FROM diseases

                LEFT JOIN clinics
                ON diseases.clinic_id = clinics.id

                ORDER BY diseases.id ASC
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
            "GET DISEASES ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};


const createDisease = async(req,res) =>
{
    try
    {
        const
        {
            name,
            clinic_id,
            description,
            symptoms
        } = req.body;

        const result =
            await pool.query(

                `
                INSERT INTO diseases
                (
                    name,
                    clinic_id,
                    description,
                    symptoms
                )

                VALUES
                (
                    $1,$2,$3,$4
                )

                RETURNING *
                `,

                [
                    name,
                    clinic_id,
                    description,
                    symptoms
                ]
            );

        res.status(201).json({

            success:true,

            message:"Disease created",

            data:result.rows[0]
        });
    }

    catch(error)
    {
        console.error(
            "CREATE DISEASE ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};


const updateDisease = async(req,res) =>
{
    try
    {
        const id =
            req.params.id;

        const
        {
            name,
            clinic_id,
            description,
            symptoms
        } = req.body;

        const result =
            await pool.query(

                `
                UPDATE diseases

                SET
                    name = $1,
                    clinic_id = $2,
                    description = $3,
                    symptoms = $4

                WHERE id = $5

                RETURNING *
                `,

                [
                    name,
                    clinic_id,
                    description,
                    symptoms,
                    id
                ]
            );

        res.status(200).json({

            success:true,

            message:"Disease updated",

            data:result.rows[0]
        });
    }

    catch(error)
    {
        console.error(
            "UPDATE DISEASE ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
}; 

const deleteDisease = async(req,res) =>
{
    try
    {
        const id =
            req.params.id;

        await pool.query(

            `
            DELETE FROM diseases

            WHERE id = $1
            `,

            [id]
        );

        res.status(200).json({

            success:true,

            message:"Disease deleted"
        });
    }

    catch(error)
    {
        console.error(
            "DELETE DISEASE ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};

module.exports = {
    getAllDiseases,
    createDisease,
    updateDisease,
    deleteDisease
};