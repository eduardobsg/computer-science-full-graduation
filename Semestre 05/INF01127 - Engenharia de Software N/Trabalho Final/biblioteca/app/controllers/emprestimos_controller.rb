class EmprestimosController < ApplicationController
  # GET /emprestimos
  # GET /emprestimos.xml
  def index
    @emprestimos = Emprestimo.all

    respond_to do |format|
      format.html # index.html.erb
      format.xml  { render :xml => @emprestimos }
    end
  end

  # GET /emprestimos/1
  # GET /emprestimos/1.xml
  def show
    @emprestimo = Emprestimo.find(params[:id])

    respond_to do |format|
      format.html # show.html.erb
      format.xml  { render :xml => @emprestimo }
    end
  end

  # GET /emprestimos/new
  # GET /emprestimos/new.xml
  def new
    @emprestimo = Emprestimo.new

    respond_to do |format|
      format.html # new.html.erb
      format.xml  { render :xml => @emprestimo }
    end
  end

  # GET /emprestimos/1/edit
  def edit
    @emprestimo = Emprestimo.find(params[:id])
  end

  # POST /emprestimos
  # POST /emprestimos.xml
  def create
    @emprestimo = Emprestimo.new(params[:emprestimo])

    respond_to do |format|
      if @emprestimo.save
        format.html { redirect_to(@emprestimo, :notice => 'Emprestimo was successfully created.') }
        format.xml  { render :xml => @emprestimo, :status => :created, :location => @emprestimo }
      else
        format.html { render :action => "new" }
        format.xml  { render :xml => @emprestimo.errors, :status => :unprocessable_entity }
      end
    end
  end

  # PUT /emprestimos/1
  # PUT /emprestimos/1.xml
  def update
    @emprestimo = Emprestimo.find(params[:id])

    respond_to do |format|
      if @emprestimo.update_attributes(params[:emprestimo])
        format.html { redirect_to(@emprestimo, :notice => 'Emprestimo was successfully updated.') }
        format.xml  { head :ok }
      else
        format.html { render :action => "edit" }
        format.xml  { render :xml => @emprestimo.errors, :status => :unprocessable_entity }
      end
    end
  end

  # DELETE /emprestimos/1
  # DELETE /emprestimos/1.xml
  def destroy
    @emprestimo = Emprestimo.find(params[:id])
    @emprestimo.destroy

    respond_to do |format|
      format.html { redirect_to(emprestimos_url) }
      format.xml  { head :ok }
    end
  end
end
