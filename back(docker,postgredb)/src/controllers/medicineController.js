const pool = require("../config/db");


const getAllMedicines = async(req,res) =>
{
    try
    {
        const result =
            await pool.query(

                `
                SELECT
                    id,
                    name,
                    stock,
                    price,
                    created_at

                FROM medicines

                ORDER BY id ASC
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
            "GET MEDICINES ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};


const createMedicine = async(req,res) =>
{
    try
    {
        const
        {
            name,
            stock,
            price
        } = req.body;

        const result =
            await pool.query(

                `
                INSERT INTO medicines
                (
                    name,
                    stock,
                    price
                )

                VALUES
                (
                    $1,$2,$3
                )

                RETURNING *
                `,

                [
                    name,
                    stock,
                    price
                ]
            );

        res.status(201).json({

            success:true,

            message:"Medicine created",

            data:result.rows[0]
        });
    }

    catch(error)
    {
        console.error(
            "CREATE MEDICINE ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};


const updateMedicine = async(req,res) =>
{
    try
    {
        const id =
            req.params.id;

        const
        {
            name,
            stock,
            price
        } = req.body;

        const result =
            await pool.query(

                `
                UPDATE medicines

                SET
                    name = $1,
                    stock = $2,
                    price = $3

                WHERE id = $4

                RETURNING *
                `,

                [
                    name,
                    stock,
                    price,
                    id
                ]
            );

        res.status(200).json({

            success:true,

            message:"Medicine updated",

            data:result.rows[0]
        });
    }

    catch(error)
    {
        console.error(
            "UPDATE MEDICINE ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};


const deleteMedicine = async(req,res) =>
{
    try
    {
        const id =
            req.params.id;

        await pool.query(

            `
            DELETE FROM medicines

            WHERE id = $1
            `,

            [id]
        );

        res.status(200).json({

            success:true,

            message:"Medicine deleted"
        });
    }

    catch(error)
    {
        console.error(
            "DELETE MEDICINE ERROR:",
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
    getAllMedicines,
    createMedicine,
    updateMedicine,
    deleteMedicine
};