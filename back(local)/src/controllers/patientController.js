const pool = require("../config/db");


const getAllPatients = async (req, res) => {

    try {

        const result = await pool.query(`

            SELECT
                patients.id,
                patients.full_name,
                patients.age,
                patients.gender,
                patients.phone,
                patients.address,
                clinics.name AS clinic_name,
                patients.created_at

            FROM patients

            LEFT JOIN clinics
            ON patients.clinic_id = clinics.id

            ORDER BY patients.id ASC

        `);

        res.status(200).json({

            success: true,

            total: result.rows.length,

            data: result.rows
        });

    } catch (err) {

        console.error(
            "GET PATIENTS ERROR:",
            err
        );

        res.status(500).json({

            success: false,

            message: err.message
        });
    }
};

const createPatient = async(req,res) =>
{
    try
    {
        const
        {
            full_name,
            age,
            gender,
            phone,
            address,
            clinic_id
        } = req.body;

        const result =
            await pool.query(

                `
                INSERT INTO patients
                (
                    full_name,
                    age,
                    gender,
                    phone,
                    address,
                    clinic_id
                )

                VALUES
                (
                    $1,$2,$3,$4,$5,$6
                )

                RETURNING *
                `,
                [
                    full_name,
                    age,
                    gender,
                    phone,
                    address,
                    clinic_id
                ]
            );

        res.status(201).json({

            success:true,

            message:"Patient created",

            data:result.rows[0]
        });
    }

    catch(error)
    {
        console.error(
            "CREATE PATIENT ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};

const updatePatient = async(req,res) =>
{
    try
    {
        const id =
            req.params.id;

        const
        {
            full_name,
            age,
            gender,
            phone,
            address,
            clinic_id
        } = req.body;

        const result =
            await pool.query(

                `
                UPDATE patients

                SET
                    full_name = $1,
                    age = $2,
                    gender = $3,
                    phone = $4,
                    address = $5,
                    clinic_id = $6

                WHERE id = $7

                RETURNING *
                `,

                [
                    full_name,
                    age,
                    gender,
                    phone,
                    address,
                    clinic_id,
                    id
                ]
            );
        
        if(result.rows.length === 0)
        {
            return res.status(404).json({
                success:false,
                message:"Patient not found"});
        }

        res.status(200).json({
            
            success:true,

            message:"Patient updated",

            data:result.rows[0]
        });
    }

    catch(error)
    {
        console.error(
            "UPDATE PATIENT ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};

const deletePatient = async(req,res) =>
{
    try
    {
        const id =
            req.params.id;

        await pool.query(

            `
            DELETE FROM patients

            WHERE id = $1
            `,

            [id]
        );

        res.status(200).json({

            success:true,

            message:"Patient deleted"
        });
    }

    catch(error)
    {
        console.error(
            "DELETE PATIENT ERROR:",
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
    getAllPatients,
    createPatient,
    updatePatient,
    deletePatient
};