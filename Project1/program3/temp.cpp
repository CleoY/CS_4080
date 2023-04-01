class Matrix{
    public:
        Matrix(){
            rows = 0;
            cols = 0;
            matrix1 = NULL;
            exist = true;
        }
        Matrix(int nRows, int nCols, bool init0){
            rows = nRows;
            cols = nCols;
            exist = true;
            
            // Allocate memory
            matrix1 = new float*[rows];
            for(int i=0; i<rows; i++){
                matrix1[i] = new float[cols];
            }

            // Initialize cells as 0's but only if user does not want to populate the matrix with random values
            if(init0){
                for(int i=0; i<rows; i++){
                    for(int j=0; j<cols; j++){
                        matrix1[i][j] = 0.0; 
                    }
                }
            }
            
        }
        Matrix(int size){ // For initializing with random values
            Matrix(size, size, false);
            std::random_device rando;
            std::mt19937 gen(rando());
            std::uniform_real_distribution<float> dist(1.0f, 10.0f);

            // Initialize matrix with random floats
            for(int i=0; i<size; i++){
                for(int j=0; j<size; j++){
                    matrix1[i][j] = dist(gen);
                }
            }
        }
        Matrix(FILE *fp){
            // Read dimensions from first line of file
            fscanf(fp, "%d %d", &rows, &cols);
            fscanf(fp, "%*c"); // Clear file reader buffer

            // Allocate space for matrix
            matrix1 = new float*[rows];
            for(int i=0; i<rows; i++){
                matrix1[i] = new float[cols];
            }

            int rowCounter = 0;
            int colCounter = 0;
            char check; // For various file checks
            float temp; 

            while(rowCounter < rows){
                while(colCounter < cols){
                    fscanf(fp, "%f", &temp);
                    matrix1[rowCounter][colCounter] = temp;
                    colCounter++;
                    check = fgetc(fp);
                    if(check == '\n'){
                        break;
                    }
                }
                colCounter = 0;
                rowCounter++;
            }
        }
        ~Matrix(){
            for(int i=0; i<rows; i++){
                delete[] matrix1[i];
            }
            delete[] matrix1;
            matrix1 = NULL;
            rows = 0;
            cols = 0;
            exist = false;
        }

        // Get functions
        int getRows(){
            return this->rows;
        }
        
        int getCols(){
            return this->cols;
        }

        Matrix operator+(const Matrix& addend){
            Matrix result(this->rows, this->cols, false); // may need to initialize with 0's (true) 

            for(int i=0; i<rows; i++){
                for(int j=0; j<rows; j++){
                    result.matrix1[i][j] = this->matrix1[i][j] + addend.matrix1[i][j];
                }
            }

            return result;
        }

        Matrix operator-(const Matrix& subtrahend){
            Matrix result(this->rows, this->cols, false); // may need to initialize with 0's (true) 

            for(int i=0; i<rows; i++){
                for(int j=0; j<rows; j++){
                    result.matrix1[i][j] = this->matrix1[i][j] - subtrahend.matrix1[i][j];
                }
            }

            return result;
        }

        Matrix operator*(const Matrix& multiplicand){
            int nRows = this->rows; // matrixA rows
            int nCols = multiplicand.cols; // matrixB cols
            Matrix result(nRows, nCols, true);
            
            for(int i=0; i<nRows; i++){
                for(int j=0; j<nCols; j++){
                    for(int k=0; k<(this->cols); k++){ // matrixA cols
                        result.matrix1[i][j] += this->matrix1[i][k] * multiplicand.matrix1[k][j];
                    }
                }
            }

            return result;
        }


        int print(){
            if(matrix1 == NULL){
                printf("Matrix has not been defined.\n");
                return 1;
            }
            for(int i=0; i<rows; i++){
                for(int j=0; j<cols; j++){
                    printf("%f ", matrix1[i][j]);
                }
                printf("\n");
            }
            return 0;
        }

    private:
        float** matrix1;
        int rows;
        int cols;
        bool exist; // = false; // initial value should not cause issues?

};